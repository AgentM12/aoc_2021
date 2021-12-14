#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include "../AdventOfCode2021.hpp"

namespace Day14 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day14_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day14_test_input.txt";

	void polymerize(const std::string& polymer, const std::unordered_map<std::string, char>& instructions, int32_t steps, std::unordered_map<std::string, uint64_t>& results) {
		for (size_t i = 0; i < polymer.length() - 1; ++i) {
			results[std::string() + polymer[i] + polymer[i + 1]]++;
		}
		for (int32_t s = 0; s < steps; ++s) {
			for (const std::pair<std::string, uint64_t>& p : std::unordered_map<std::string, uint64_t>(results)) {
				if (p.second > 0) {
					results[std::string() + p.first[0] + instructions.at(p.first)] += p.second;
					results[std::string() + instructions.at(p.first) + p.first[p.first.length() - 1]] += p.second;
					results[p.first] -= p.second;
				}
			}
		}
	}

	uint64_t tally(const std::unordered_map<std::string, uint64_t>& results, const std::string& polymer) {
		std::unordered_map<char, uint64_t> freq;
		for (const std::pair<std::string, uint64_t>& p : results) {
			freq[p.first[0]] += p.second;
			freq[p.first[p.first.size() - 1]] += p.second;
		}
		freq[polymer[0]]++;
		freq[polymer[polymer.size() - 1]]++;

		uint64_t min = UINT64_MAX, max = 0;
		for (const std::pair<char, uint64_t> p : freq) {
			uint64_t v = p.second / 2;
			if (v > max) {
				max = v;
			}
			if (v < min) {
				min = v;
			}
		}
		return max - min;
	}

	uint64_t part1(const std::string& polymer, const std::unordered_map<std::string, char>& instructions) {
		std::unordered_map<std::string, uint64_t> results;
		polymerize(polymer, instructions, 10, results);
		return tally(results, polymer);
	}

	uint64_t part2(const std::string& polymer, const std::unordered_map<std::string, char>& instructions) {
		std::unordered_map<std::string, uint64_t> results;
		polymerize(polymer, instructions, 40, results);
		return tally(results, polymer);
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::string polymer;
		std::unordered_map<std::string, char> instructions;
		for (size_t i = 0; i < rx.size(); ++i) {
			const std::string& line = rx[i];
			if (i == 0) {
				polymer = line;
			} else if (!line.empty()) {
				instructions[line.substr(0, 2)] = line[6];
			}
		}

		uint64_t p1 = part1(polymer, instructions);
		printf_s("Solution 14.1: %llu\n", p1);

		uint64_t p2 = part2(polymer, instructions);
		printf_s("Solution 14.2: %llu\n", p2);

		return 0;
	}
}