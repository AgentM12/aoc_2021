#include <iostream>
#include <vector>
#include <iterator>
#include "../AdventOfCode2021.hpp"

namespace Day3 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day3_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day3_test_input.txt";

	std::vector<int32_t> most_common(const std::vector<int32_t> dat, size_t sz) {
		std::vector<int32_t> counts;
		bool first = true;
		for (int32_t b : dat) {
			for (int32_t i = 0; i < sz; i++) {
				int32_t v = (b >> (sz - i - 1)) & 1;
				if (first) counts.push_back(v);
				else counts[i] += v;
			}
			first = false;
		}
		return counts;
	}

	int32_t part1(const std::vector<int32_t>& input, size_t sz) {
		size_t total = input.size();
		std::vector<int32_t> counts = most_common(input, sz);
		int32_t g = 0;
		int32_t e = 0;
		for (int32_t n : counts) {
			g <<= 1;
			e <<= 1;
			if (n >= (total + 1) / 2) g |= 1;
			else e |= 1;
		}
		return g * e;
	}

	std::vector<int32_t> filter(const std::vector<int32_t>& input, int32_t index, size_t sz, bool inverse) {
		size_t total = input.size();
		std::vector<int32_t> counts = most_common(input, sz);
		bool mc = (counts[index] >= (total + 1) / 2) ^ inverse;
		std::vector<int32_t> data;
		for (int32_t b : input) {
			if (!(static_cast<bool>(b >> (sz - 1 - index) & 1) ^ mc)) {
				data.push_back(b);
			}
		}
		return data;
	}

	int32_t part2(const std::vector<int32_t>& input, size_t sz) {
		std::vector<int32_t> ogr = input;
		std::vector<int32_t> csr = input;
		for (int32_t i = 0; i < sz && (ogr.size() > 1 || csr.size() > 1); i++) {
			if (ogr.size() > 1) ogr = filter(ogr, i, sz, false);
			if (csr.size() > 1) csr = filter(csr, i, sz, true);
		}
		return ogr[0] * csr[0];
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::vector<std::int32_t> bin_list;
		size_t sz = rx[0].length();
		for (std::string v : rx) {
			int32_t i = stoi(v, 0, 2);
			bin_list.push_back(i);
		}

		int32_t p1 = part1(bin_list, sz);
		printf_s("Solution 3.1: %d\n", p1);

		int32_t p2 = part2(bin_list, sz);
		printf_s("Solution 3.2: %d\n", p2);

		return 0;
	}
}