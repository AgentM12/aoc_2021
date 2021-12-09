#include <iostream>
#include <vector>
#include <iterator>
#include <array>
#include <algorithm>
#include "../AdventOfCode2021.hpp"

namespace Day9 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day9_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day9_test_input.txt";

	int32_t part1(const std::vector<uint8_t>& input, size_t width, size_t height) {
		int32_t count = 0;

		for (size_t y = 0; y < height; ++y) {
			for (size_t x = 0; x < width; ++x) {
				size_t index = (y * width + x);
				uint8_t cur = input[index];
				if (x > 0 && input[index - 1] <= cur) continue;
				if (x < width - 1 && input[index + 1] <= cur) continue;
				if (y > 0 && input[index - width] <= cur) continue;
				if (y < height - 1 && input[index + width] <= cur) continue;

				count += 1 + cur;
			}
		}
		return count;
	}

	int32_t expand(size_t x, size_t y, size_t w, size_t h, int32_t c, std::vector<size_t>& vs, const std::vector<uint8_t>& inp) {
		size_t index = (y * w + x);
		if (std::find(vs.begin(), vs.end(), index) != vs.end()) {
			return 0;
		}
		vs.push_back(index);

		uint8_t cur = inp[index];
		int32_t n = 0;
		if (x > 0 && inp[index - 1] > cur && inp[index - 1] < 9) n += expand(x - 1, y, w, h, c, vs, inp);
		if (x < w - 1 && inp[index + 1] > cur && inp[index + 1] < 9) n += expand(x + 1, y, w, h, c, vs, inp);
		if (y > 0 && inp[index - w] > cur && inp[index - w] < 9) n += expand(x, y - 1, w, h, c, vs, inp);
		if (y < h - 1 && inp[index + w] > cur && inp[index + w] < 9) n += expand(x, y + 1, w, h, c, vs, inp);

		return c + n;
	}

	int32_t part2(const std::vector<uint8_t>& input, size_t width, size_t height) {
		std::array<int32_t, 3> top3{0, 0, 0};

		for (size_t y = 0; y < height; ++y) {
			for (size_t x = 0; x < width; ++x) {
				size_t index = (y * width + x);
				uint8_t cur = input[index];
				if (x > 0 && input[index - 1] <= cur) continue;
				if (x < width - 1 && input[index + 1] <= cur) continue;
				if (y > 0 && input[index - width] <= cur) continue;
				if (y < height - 1 && input[index + width] <= cur) continue;

				std::vector<size_t> vs;
				int32_t sz = expand(x, y, width, height, 1, vs, input);
				for (size_t i = 0; i < top3.size(); ++i) {
					int32_t sz_t = top3[i];
					if (sz >= sz_t) {
						auto temp = top3[i];
						top3[i] = sz;
						sz = temp;
					}
				}
			}
		}
		return top3[0] * top3[1] * top3[2];
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		size_t w = rx.size(), h = rx[0].length();
		std::vector<uint8_t> input(w * h);

		size_t y = 0;
		for (const std::string& line : rx) {
			size_t x = 0;
			for (char c : line) {
				input[y * w + x] = c - '0';
				++x;
			}
			++y;
		}

		int32_t p1 = part1(input, w, h);
		printf_s("Solution 9.1: %d\n", p1);

		int32_t p2 = part2(input, w, h);
		printf_s("Solution 9.2: %d\n", p2);

		return 0;
	}
}