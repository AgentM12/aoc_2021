#include <iostream>
#include <vector>
#include <iterator>
#include <array>
#include "../AdventOfCode2021.hpp"

namespace Day6 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day6_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day6_test_input.txt";

	constexpr size_t MAX_DAYS = 9;

	uint64_t simulate(const std::array<uint64_t, MAX_DAYS>& input, const int32_t days) {
		std::array<uint64_t, MAX_DAYS> mut_input{};
		std::copy(input.begin(), input.end(), mut_input.begin());
		for (int32_t day = 0; day < days; ++day) {
			mut_input[(day + MAX_DAYS - 2) % MAX_DAYS] += mut_input[day % MAX_DAYS];
		}
		uint64_t sum = 0;
		for (int32_t i = 0; i < MAX_DAYS; ++i) {
			sum += mut_input[i];
		}
		return sum;
	}

	uint64_t part1(const std::array<uint64_t, MAX_DAYS>& input) {
		return simulate(input, 80);
	}

	uint64_t part2(const std::array<uint64_t, MAX_DAYS>& input) {
		return simulate(input, 256);
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::array<uint64_t, MAX_DAYS> population{0, 0, 0, 0, 0, 0, 0, 0, 0};
		for (const char c : rx[0]) {
			size_t n = static_cast<size_t>(c) - '0';
			if (n < MAX_DAYS) {
				population[n]++;
			}
		}

		uint64_t p1 = part1(population);
		printf_s("Solution 6.1: %llu\n", p1);

		uint64_t p2 = part2(population);
		printf_s("Solution 6.2: %llu\n", p2);

		return 0;
	}
}