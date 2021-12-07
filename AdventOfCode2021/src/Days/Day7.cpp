#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "../AdventOfCode2021.hpp"

namespace Day7 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day7_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day7_test_input.txt";

	int32_t median(const std::vector<int32_t>& vec) {
		// Assume sorted
		size_t size = vec.size();
		if (size % 2 != 0)
			return vec[size / 2];
		return static_cast<int32_t>((static_cast<double>(vec[(size - 1) / 2] + vec[size / 2]) / 2.0) + 0.5);
	}

	uint64_t part1(const std::vector<int32_t>& input) {
		int32_t m = median(input);
		uint64_t fuel_used = 0;
		for (int32_t i : input) {
			fuel_used += static_cast<uint64_t>(std::abs(i - m));
		}
		return fuel_used;
	}

	uint64_t sumto(int32_t x) {
		uint64_t sum = 0;
		for (; x > 0; --x) {
			sum += x;
		}
		return sum;
	}

	uint64_t fuel_cost_high(const std::vector<int32_t>& input, int32_t convergence_point) {
		uint64_t sum = 0;
		for (int32_t i : input) {
			sum += sumto(std::abs(i - convergence_point));
		}
		return sum;
	}

	uint64_t part2(const std::vector<int32_t>& input) {
		uint64_t input_sum = 0;
		for (int32_t i : input) {
			input_sum += static_cast<uint64_t>(i);
		}
		
		int32_t avg = static_cast<int32_t>(input_sum / input.size());
		
		uint64_t fu_rd = fuel_cost_high(input, avg);
		uint64_t fu_ru = fuel_cost_high(input, avg + 1);
		
		if (fu_rd > fu_ru)
			return fu_ru;
		return fu_rd;
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::vector<int32_t> positions;
		bool has_value = false;
		int32_t num;
		for (std::string& line : rx) {
			num = 0;
			for (char c : line) {
				int32_t v = (c - '0');
				if (v >= 0 && v < 10) {
					num *= 10;
					num += v;
					has_value = true;
				} else if (has_value) {
					positions.push_back(num);
					num = 0;
					has_value = false;
				}
			}
		}
		if (has_value) positions.push_back(num);

		std::sort(positions.begin(), positions.end());
		//for (int32_t pos : positions) {
		//	std::cout << pos << std::endl;
		//}
		uint64_t p1 = part1(positions);
		printf_s("Solution 7.1: %llu\n", p1);

		uint64_t p2 = part2(positions);
		printf_s("Solution 7.2: %llu\n", p2);

		return 0;
	}
}