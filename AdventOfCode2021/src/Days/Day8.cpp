#include <iostream>
#include <vector>
#include <iterator>
#include <array>
#include "../AdventOfCode2021.hpp"

namespace Day8 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day8_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day8_test_input.txt";

	typedef uint8_t s7d;

	struct Entry {
		std::array<s7d, 10> signals;
		std::array<s7d, 4> output;
	};

	s7d _a = 1, _b = 2, _c = 4, _d = 8, _e = 16, _f = 32, _g = 64;
	s7d flags[7]{_a, _b, _c, _d, _e, _f, _g};

	std::string visualize(s7d s7digit) {
		std::string str = "";

		if (s7digit & _a) str += "a";
		if (s7digit & _b) str += "b";
		if (s7digit & _c) str += "c";
		if (s7digit & _d) str += "d";
		if (s7digit & _e) str += "e";
		if (s7digit & _f) str += "f";
		if (s7digit & _g) str += "g";

		return str;
	}

	size_t len(s7d s7digit) {
		size_t s = 0;
		for (s7d d : flags) {
			if (s7digit & d) ++s;
		}
		return s;
	}

	int32_t part1(const std::vector<Entry>& input) {
		int32_t sum = 0;
		for (const Entry& e : input) {
			for (s7d i : e.output) {
				size_t s = len(i);
				if (s == 2 || s == 3 || s == 4 || s == 7) ++sum;
			}
		}
		return sum;
	}

	int32_t part2(const std::vector<Entry>& input) {
		int32_t count = 0;
		std::array<s7d, 10> resolved_mappings{};
		std::array<s7d, 3> candidates_235{};
		std::array<s7d, 3> candidates_069{};
		for (const Entry& e : input) {
			size_t i_235 = 0;
			size_t i_069 = 0;
			for (s7d d : e.signals) {
				switch (len(d)) {
					case 2:
						resolved_mappings[1] = d;
						break;
					case 3:
						resolved_mappings[7] = d;
						break;
					case 4:
						resolved_mappings[4] = d;
						break;
					case 7:
						resolved_mappings[8] = d;
						break;
					case 5:
						candidates_235[i_235++] = d;
						break;
					case 6:
						candidates_069[i_069++] = d;
						break;
					default:
						throw std::invalid_argument(visualize(d) + " is not a valid s7d");
				}
			}

			// External mappings deduced
			s7d x_cf = resolved_mappings[1];
			s7d x_a = resolved_mappings[7] - resolved_mappings[1];
			s7d x_bd = resolved_mappings[4] - resolved_mappings[1];
			s7d x_eg = resolved_mappings[8] - resolved_mappings[4] - x_a;

			// _235 and _069 digits deduced
			for (s7d d : candidates_235) {
				if ((d & x_bd) == x_bd) {
					resolved_mappings[5] = d;
				} else if ((d & x_eg) == x_eg) {
					resolved_mappings[2] = d;
				} else {
					resolved_mappings[3] = d;
				}
			}

			for (s7d d : candidates_069) {
				if (!((d & x_cf) == x_cf)) {
					resolved_mappings[6] = d;
				} else if (!((d & x_eg) == x_eg)) {
					resolved_mappings[9] = d;
				} else {
					resolved_mappings[0] = d;
				}
			}

			// Resolving digits
			int32_t out_digits = 0;
			for (s7d d : e.output) {
				for (int32_t i = 0; i < resolved_mappings.size(); ++i) {
					s7d xd = resolved_mappings[i];
					if (d == xd) {
						out_digits *= 10;
						out_digits += i;
					}
				}
			}
			count += out_digits;
		}
		return count;
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::vector<Entry> entries;

		size_t counter = 0;
		s7d num = 0;
		bool has_value = false;
		Entry e{};
		for (std::string line : rx) {
			for (char c : line) {
				if (c >= 'a' && c <= 'g') {
					num |= flags[(c - 'a')];
					has_value = true;
				} else if (has_value) {
					if (counter < 10) {
						e.signals[counter] = num;
					} else if (counter < 14) {
						e.output[counter - 10] = num;
					}
					if (counter == 13) {
						entries.push_back(e);
						e = Entry{};
					}
					counter = (++counter) % 14;
					num = 0;
					has_value = false;
				}
			}
			if (has_value) {
				if (counter < 10) {
					e.signals[counter] = num;
				} else if (counter < 14) {
					e.output[counter - 10] = num;
				}
				if (counter == 13) {
					entries.push_back(e);
					e = Entry{};
				}
				counter = (++counter) % 14;
				num = 0;
				has_value = false;
			}
		}

		int32_t p1 = part1(entries);
		printf_s("Solution 8.1: %d\n", p1);

		int32_t p2 = part2(entries);
		printf_s("Solution 8.2: %d\n", p2);

		return 0;
	}
}