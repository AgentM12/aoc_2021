#include <iostream>
#include <vector>
#include <iterator>
#include <array>
#include "../AdventOfCode2021.hpp"

namespace Day11 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day11_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day11_test_input.txt";

	typedef int8_t oct;

	void flash(std::array<oct, 100>& input, int32_t& flashed) {
		for (size_t y = 0; y < 10; ++y) {
			for (size_t x = 0; x < 10; ++x) {
				oct i = input[(y * 10) + x];
				if (i > 9) {
					flashed += 1;
					input[(y * 10) + x] = -1;
					if (y > 0) {
						if (input[(y - 1) * 10 + x] > -1) input[(y - 1) * 10 + x]++;
						if (x > 0 && input[(y - 1) * 10 + (x - 1)] > -1) input[(y - 1) * 10 + (x - 1)]++;
						if (x < 9 && input[(y - 1) * 10 + (x + 1)] > -1) input[(y - 1) * 10 + (x + 1)]++;
					}

					if (y < 9) {
						if (input[(y + 1) * 10 + x] > -1) input[(y + 1) * 10 + x]++;
						if (x > 0 && input[(y + 1) * 10 + (x - 1)] > -1) input[(y + 1) * 10 + (x - 1)]++;
						if (x < 9 && input[(y + 1) * 10 + (x + 1)] > -1) input[(y + 1) * 10 + (x + 1)]++;
					}

					if (x > 0 && input[(y * 10) + (x - 1)] > -1) input[(y * 10) + (x - 1)]++;
					if (x < 9 && input[(y * 10) + (x + 1)] > -1) input[(y * 10) + (x + 1)]++;
				}
			}
		}
	}

	int32_t simulate(std::array<oct, 100> input, bool part2) {
		int32_t flashes = 0, step = 1;
		for (; part2 || step <= 100; ++step) {
			int32_t flashed = 0;
			for (size_t i = 0; i < input.size(); ++i) {
				if (input[i]++ == 9) ++flashed;
			}

			int32_t flash_count = 0;
			while (flashed > 0) {
				flashed = 0;
				flash(input, flashed);
				flash_count += flashed;
			}
			if (part2 && flash_count >= 100) return step;

			for (size_t i = 0; i < input.size(); ++i) {
				if (input[i] == -1) input[i] = 0;
			}
			flashes += flash_count;
		}
		return flashes;
	}

	int32_t part1(const std::array<oct, 100>& input) {
		return simulate(input, false);
	}

	int32_t part2(const std::array<oct, 100>& input) {
		return simulate(input, true);
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::array<oct, 100> inp{};
		size_t i = 0;
		for (const std::string& line : rx) {
			for (char c : line) {
				inp[i] = c - '0';
				++i;
			}
		}

		int32_t p1 = part1(inp);
		printf_s("Solution 11.1: %d\n", p1);

		int32_t p2 = part2(inp);
		printf_s("Solution 11.2: %d\n", p2);

		return 0;
	}
}