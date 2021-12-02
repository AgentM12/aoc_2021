#include <iostream>
#include <vector>
#include <iterator>
#include "../AdventOfCode2021.hpp"

namespace Day1 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day1_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day1_test_input.txt";

	int32_t part1(const std::vector<int32_t>& input) {
		int32_t c = 0;
		int32_t prev;
		bool first = true;

		for (int32_t val : input) {
			if (!first) {
				if (prev < val) {
					c++;
				}
			}
			first = false;
			prev = val;
		}

		return c;
	}

	int32_t part2(const std::vector<int32_t>& input) {
		int32_t c = 0;
		int32_t prev[3]{};
		int32_t setup = 3;

		for (int32_t val : input) {
			if (setup > 0) {
				prev[--setup] = val;
				continue;
			}
			if (prev[0] < val) {
				c++;
			}
			prev[0] = prev[1];
			prev[1] = prev[2];
			prev[2] = val;
		}

		return c;
	}

	int run() {
		std::vector<int32_t> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		int32_t p1 = part1(rx);
		printf_s("Solution 1.1: %d\n", p1);

		int32_t p2 = part2(rx);
		printf_s("Solution 1.2: %d\n", p2);

		return 0;
	}
}