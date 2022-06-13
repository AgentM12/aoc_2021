#include <iostream>
#include <vector>
#include <iterator>
#include "../AdventOfCode2021.hpp"

namespace Day16 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day16_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day16_test_input.txt";

	struct State {
		uint64_t val;
		uint64_t ver;
		size_t ptr;

		State() : val(0), ver(0), ptr(0) {}
		State(const State& other, uint64_t ver) :val(other.val), ver(other.ver + ver), ptr(other.ptr) {}
		State(uint64_t val, uint64_t ver, size_t ptr) : val(val), ver(ver), ptr(ptr) {}
	};

	State read(const char* packet, size_t start);

	uint64_t decode(const char* str, size_t start, size_t size) {
		uint64_t v = 0;
		for (size_t i = start; i < start + size; ++i) {
			v = (v << 1) + static_cast<uint64_t>(str[i]) - '0';
		}
		return v;
	}

	std::string hex_string_to_bin_string(const std::string& str) {
		std::string result = "";
		for (char c : str) {
			uint8_t d = c - '0';
			if (d > 9) d = 10 + (c - 'A');

			result += (d & 0b1000) ? "1" : "0";
			result += (d & 0b0100) ? "1" : "0";
			result += (d & 0b0010) ? "1" : "0";
			result += (d & 0b0001) ? "1" : "0";
		}
		return result;
	}

	uint64_t sum(const std::vector<uint64_t>& operands) {
		uint64_t s = 0;
		for (uint64_t o : operands) s += o;
		return s;
	}

	uint64_t prod(const std::vector<uint64_t>& operands) {
		uint64_t s = 1;
		for (uint64_t o : operands) s *= o;
		return s;
	}

	uint64_t min(const std::vector<uint64_t>& operands) {
		uint64_t s = UINT64_MAX;
		for (uint64_t o : operands) if (o < s) s = o;
		return s;
	}

	uint64_t max(const std::vector<uint64_t>& operands) {
		uint64_t s = 0;
		for (uint64_t o : operands) if (o > s) s = o;
		return s;
	}

	State read_literal(const char* packet, size_t i) {
		std::string out = "";
		bool x;
		do {
			for (size_t j = 1; j < 5; ++j) out += packet[i + j];
		} while (x = packet[i] == '1', i += 5, x);
		return State(decode(out.c_str(), 0, out.size()), 0, i);
	}

	State read_operator(const char* packet, size_t start, uint8_t type_id) {
		std::vector<uint64_t> operands;

		State state{};
		if (packet[start] == '0') {
			size_t subs_total_len = decode(packet, start + 1, 15);

			for (size_t i = start + 16; i < start + 16 + subs_total_len;) {
				State tempState = read(packet, i);
				i = state.ptr = tempState.ptr;
				state.ver += tempState.ver;
				operands.push_back(tempState.val);
			}
		} else {
			size_t num_subs_cont = decode(packet, start + 1, 11);
			state.ptr = start + 12;
			for (size_t i = 0; i < num_subs_cont; ++i) {
				State tempState = read(packet, state.ptr);
				state.ptr = tempState.ptr;
				state.ver += tempState.ver;
				operands.push_back(tempState.val);
			}
		}

		// Resolve operator
		switch (type_id) {
			case 0: state.val = sum(operands); break;
			case 1: state.val = prod(operands); break;
			case 2: state.val = min(operands); break;
			case 3: state.val = max(operands); break;
			case 5: state.val = operands[0] > operands[1]; break;
			case 6: state.val = operands[0] < operands[1]; break;
			case 7: state.val = operands[0] == operands[1]; break;
		}
		return state;
	}

	State read(const char* packet, size_t start) {
		uint8_t version = static_cast<uint8_t>(decode(packet, start, 3));
		uint8_t type_id = static_cast<uint8_t>(decode(packet, start + 3, 3));

		if (type_id == 4) return State(read_literal(packet, start + 6), version);
		return State(read_operator(packet, start + 6, type_id), version);
	}

	uint64_t part1(const State& input) { return input.ver; }

	uint64_t part2(const State& input) { return input.val; }

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::string input = hex_string_to_bin_string(rx[0]);

		State state = read(input.c_str(), 0);

		uint64_t p1 = part1(state);
		printf_s("Solution 16.1: %llu\n", p1);

		uint64_t p2 = part2(state);
		printf_s("Solution 16.2: %llu\n", p2);

		return 0;
	}
}