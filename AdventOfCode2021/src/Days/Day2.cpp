#include <iostream>
#include <vector>
#include <iterator>
#include <assert.h>
#include "../AdventOfCode2021.hpp"

namespace Day2 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day2_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day2_test_input.txt";

	int32_t part1(const std::vector<std::string>& input) {
		int32_t depth = 0;
		int32_t h_pos = 0;
		for (std::string d : input) {
			size_t index = d.find(" ");
			int32_t v = strtol(d.substr(index, d.length() - index).c_str(), nullptr, 10);
			
			switch (d[0]) {
				case 'u':
					depth -= v;
					break;
				case 'd':
					depth += v;
					break;
				case 'f':
					h_pos += v;
					break;
			}
		}
		return depth * h_pos;
	}

	int32_t part2(const std::vector<std::string>& input) {
		int32_t aim = 0;
		int32_t depth = 0;
		int32_t h_pos = 0;
		for (std::string d : input) {
			size_t index = d.find(" ");
			int32_t v = strtol(d.substr(index, d.length() - index).c_str(), nullptr, 10);

			switch (d[0]) {
				case 'u':
					aim -= v;
					break;
				case 'd':
					aim += v;
					break;
				case 'f':
					h_pos += v;
					depth += aim * v;
					break;
			}
		}
		return depth * h_pos;
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		int32_t p1 = part1(rx);
		printf_s("Solution 2.1: %d\n", p1);

		int32_t p2 = part2(rx);
		printf_s("Solution 2.2: %d\n", p2);

		return 0;
	}
}