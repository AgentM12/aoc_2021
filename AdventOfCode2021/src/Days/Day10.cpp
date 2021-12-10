#include <iostream>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <stack>
#include <algorithm>
#include "../AdventOfCode2021.hpp"

namespace Day10 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day10_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day10_test_input.txt";

	////////////////////////// Lookup tables / dicts / maps //////////////////////////
	constexpr inline int32_t error_score_for(const char& c) {
		switch (c) {
			case ')': return 3; case ']': return 57; case '}': return 1197; case '>': return 25137;
			default: throw std::invalid_argument(c + " is an invalid symbol");
		}
	}

	constexpr inline int32_t completing_score_of(const char& c) {
		switch (c) {
			case '(': return 1; case '[': return 2; case '{': return 3; case '<': return 4;
			default: throw std::invalid_argument(c + " is an invalid symbol");
		}
	}

	constexpr inline char matching_close_symbol(const char& c) {
		switch (c) {
			case '(': return ')'; case '[': return ']'; case '{': return '}'; case '<': return '>';
			default: throw std::invalid_argument(c + " is an invalid symbol");
		}
	}

	constexpr inline bool is_open_symbol(const char& c) {
		switch (c) {
			case '(': case '[': case '{': case '<': return true;
			case ')': case ']': case '}': case '>': return false;
			default: throw std::invalid_argument(c + " is an invalid symbol");
		}
	}
	//////////////////////////////////////////////////////////////////////////////////


	int32_t part1(const std::vector<std::string>& input, std::vector<std::string>& output_malformed_filtered) {
		int32_t score = 0;
		for (const std::string& line : input) {
			std::stack<char> seq;
			bool malformed = false;
			for (char c : line) {
				if (is_open_symbol(c)) {
					seq.push(c);
				} else {
					if (seq.size() <= 0) throw std::invalid_argument("Stack was empty!");
					if (matching_close_symbol(seq.top()) != c) {
						score += error_score_for(c);
						malformed = true;
						break;
					}
					seq.pop();
				}
			}
			if (!malformed) output_malformed_filtered.push_back(line); // lineup for part 2
		}
		return score;
	}

	uint64_t part2(const std::vector<std::string>& input) {
		std::vector<uint64_t> total_scores;
		for (const std::string& line : input) {
			std::stack<char> seq;
			for (char c : line) {
				if (is_open_symbol(c)) {
					seq.push(c);
				} else {
					if (seq.size() <= 0) throw std::invalid_argument("Stack was empty!");
					if (matching_close_symbol(seq.top()) != c) throw std::invalid_argument("Non-matching close symbol found. This should not be possible!");
					seq.pop();
				}
			}

			uint64_t subscore = 0;
			while (!seq.empty()) {
				subscore *= 5;
				subscore += completing_score_of(seq.top());
				seq.pop();
			}
			total_scores.push_back(subscore);
		}
		std::sort(total_scores.begin(), total_scores.end());
		return total_scores[total_scores.size() / 2];
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::vector<std::string> filtered_input;
		int32_t p1 = part1(rx, filtered_input);
		printf_s("Solution 10.1: %d\n", p1);

		uint64_t p2 = part2(filtered_input);
		printf_s("Solution 10.2: %llu\n", p2);

		return 0;
	}
}