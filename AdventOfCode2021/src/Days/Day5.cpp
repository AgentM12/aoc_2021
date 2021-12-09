#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <chrono>
#include "../AdventOfCode2021.hpp"

namespace Day5 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day5_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day5_test_input.txt";

	struct Line {
		uint16_t x1;
		uint16_t y1;
		uint16_t x2;
		uint16_t y2;
	};

	int32_t shared(const std::vector<Line>& input, bool part2) {
		std::unordered_map<uint32_t, uint8_t> coords; // Alloc and Dealloc costs ~0.20s
		for (const Line& line : input) {
			if (part2 || line.x1 == line.x2 || line.y1 == line.y2) {
				uint16_t x = line.x1;
				uint16_t y = line.y1;
				coords[static_cast<uint32_t>(x) << 16 | y] += 1;
				while (x != line.x2 || y != line.y2) {
					// step
					if (x < line.x2) ++x;
					else if (x > line.x2) --x;
					if (y < line.y2) ++y;
					else if (y > line.y2) --y;

					// mark
					coords[static_cast<uint32_t>(x) << 16 | y] += 1;
				}
			}
		}
		int32_t sum = 0;
		for (const auto& p : coords) {
			if (p.second > 1) sum++;
		}
		return sum;
	}

	int32_t part1(const std::vector<Line>& input) {
		return shared(input, false);
	}

	int32_t part2(const std::vector<Line>& input) {
		return shared(input, true);
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::vector<Line> lines;
		for (const std::string& line : rx) {
			Line l{};
			sscanf_s(line.c_str(), "%hu,%hu -> %hu,%hu", &l.x1, &l.y1, &l.x2, &l.y2);
			lines.push_back(l);
		}
		
		auto start1 = std::chrono::high_resolution_clock::now();
		int32_t p1 = part1(lines);
		auto stop1 = std::chrono::high_resolution_clock::now();
		auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
		printf_s("Solution 5.1: %d [%lld ms]\n", p1, duration1.count());

		//printf_s("Solution 5.1: %d\n", p1);

		auto start2 = std::chrono::high_resolution_clock::now();
		int32_t p2 = part2(lines);
		auto stop2 = std::chrono::high_resolution_clock::now();
		auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);
		printf_s("Solution 5.2: %d [%lld ms]\n", p2, duration2.count());

		//printf_s("Solution 5.2: %d\n", p2);
		
		return 0;
	}
}