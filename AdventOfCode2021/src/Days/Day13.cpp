#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include "../AdventOfCode2021.hpp"

namespace Day13 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day13_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day13_test_input.txt";

	struct instruction {
		bool hz;
		int16_t val;
	};

	typedef int32_t point;

	void fold(const std::vector<point>& inPoints, std::vector<point>& outPoints, const instruction& ins) {
		for (const point& p : inPoints) {
			int16_t x = p & 0xFFFF;
			int16_t y = (p >> 16) & 0xFFFF;
			point new_c = p;
			if (ins.hz && (x > ins.val)) {
				new_c = (y << 16) + (2 * ins.val - x);
				if (std::find(inPoints.begin(), inPoints.end(), new_c) == inPoints.end()) {
					outPoints.push_back(new_c);
				}
				continue;
			} else if (!ins.hz && y > ins.val) {
				new_c = x + ((2 * ins.val - y) << 16);
				if (std::find(inPoints.begin(), inPoints.end(), new_c) == inPoints.end()) {
					outPoints.push_back(new_c);
				}
				continue;
			}
			outPoints.push_back(new_c);
		}
	}

	int32_t part1(const std::vector<instruction>& instructions, const std::vector<point>& points) {
		std::vector<point> outPoints;
		fold(points, outPoints, instructions[0]);
		return static_cast<int32_t>(outPoints.size());
	}

	std::string vis(const std::vector<point>& points) {
		int16_t width = 3;
		int16_t height = 3;
		for (const point& p : points) {
			int16_t x = p & 0xFFFF;
			int16_t y = (p >> 16) & 0xFFFF;
			if (x + 2 > width) {
				width = x + 2;
			}
			if (y + 2 > height) {
				height = y + 2;
			}
		}

		std::string output = std::string(static_cast<size_t>(width) * height, '.');
		for (const point& p : points) {
			int16_t x = p & 0xFFFF;
			int16_t y = (p >> 16) & 0xFFFF;
			output[static_cast<size_t>(y) * width + x] = '#';
		}

		std::stringstream lines;
		for (int16_t y = 0; y < height; ++y) {
			lines << std::endl << output.substr(static_cast<size_t>(y) * width, width);
		}
		return lines.str();
	}

	std::string part2(const std::vector<instruction>& instructions, const std::vector<point>& points) {
		std::vector<point> outPoints;
		std::vector<point> swapPoints = points;
		for (const instruction& ins : instructions) {
			fold(swapPoints, outPoints, ins);
			swapPoints = outPoints;
			outPoints.clear();
		}
		return vis(swapPoints);
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::vector<instruction> instructions;
		std::vector<point> points;
		for (const std::string& line : rx) {
			if (line.empty()) continue;
			if (line[0] == 'f') { // fold along x=N
				instruction i{line[11] == 'x', static_cast<int16_t>(std::stoi(line.substr(line.find('=') + 1, line.size())))};
				instructions.push_back(i);
			} else {
				size_t i = line.find(',');
				point p = std::stoi(line.substr(i + 1, line.size()));
				p <<= 16;
				p += std::stoi(line.substr(0, i));
				points.push_back(p);
			}
		}

		int32_t p1 = part1(instructions, points);
		printf_s("Solution 13.1: %d\n", p1);

		std::string p2 = part2(instructions, points);
		
		const char* ANSWER = "PFKLKCFP"; // Deduced from actual answer, for display purposes only.
		printf_s("Solution 13.2: %s%s\n", ANSWER, p2.c_str());

		return 0;
	}
}