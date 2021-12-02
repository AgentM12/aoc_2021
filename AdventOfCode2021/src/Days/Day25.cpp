#include <iostream>
#include <vector>
#include <iterator>
#include "../AdventOfCode2021.hpp"

namespace Day25 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day25_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day25_test_input.txt";

	int32_t part1(const std::vector<int32_t>& input) {
		return 0;
	}

	int32_t part2(const std::vector<int32_t>& input) {
		return 0;
	}

	int run() {
		std::vector<int32_t> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		int32_t p1 = part1(rx);
		printf_s("Solution 25.1: %d\n", p1);

		int32_t p2 = part2(rx);
		printf_s("Solution 25.2: %d\n", p2);

		return 0;
	}
}