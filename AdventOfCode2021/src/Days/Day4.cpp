#include <iostream>
#include <vector>
#include <iterator>
#include "../AdventOfCode2021.hpp"

namespace Day4 {
	constexpr bool TEST = false;
	constexpr int32_t BOARD_SZ = 5;

	constexpr auto INPUT_FILE_PATH = "data/day4_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day4_test_input.txt";

	int32_t score(const std::vector<int32_t>& board) {
		int32_t sum = 0;
		for (int32_t i : board) {
			if (i > 0) sum += i;
		}
		return sum;
	}

	int32_t bingo(const std::vector<int32_t>& calls, std::vector<std::vector<int32_t>> boards, bool is_part2) {
		std::vector<std::vector<int32_t>> new_boards;
		for (int32_t call : calls) {
			size_t total_boards = boards.size();
			for (std::vector<int32_t>& board : boards) {
				bool remove_board = false;
				for (size_t i = 0; i < board.size(); i++) {
					if (board[i] == call) {
						board[i] = -1;

						// Check row and column
						int32_t r = static_cast<int32_t>(i / BOARD_SZ);
						int32_t c = i % BOARD_SZ;
						int32_t h = BOARD_SZ - 1;
						int32_t v = BOARD_SZ - 1;
						for (int32_t y = 0; y < BOARD_SZ; y++) {
							for (int32_t x = 0; x < BOARD_SZ; x++) {
								if (((y == r) ^ (x == c)) && (board[static_cast<size_t>(y) * BOARD_SZ + x] == -1)) {
									if (y == r) {
										h--;
									} else if (x == c) {
										v--;
									}
									if (h == 0 || v == 0) {
										remove_board = true;
										if (total_boards-- == 1 || !is_part2) {
											return score(board) * call;
										}
										goto UPDATE_BOARD;
									}
								}
							}
						}
						break; // A number can only appear once on a board.
					}
				}
			UPDATE_BOARD:
				if (!remove_board) {
					new_boards.push_back(board);
				}
			}
			boards = new_boards;
			new_boards = std::vector<std::vector<int32_t>>();
		}

		return -1;
	}

	int32_t part1(const std::vector<int32_t>& calls, std::vector<std::vector<int32_t>> boards) {
		return bingo(calls, boards, false);
	}

	int32_t part2(const std::vector<int32_t>& calls, std::vector<std::vector<int32_t>> boards) {
		return bingo(calls, boards, true);
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::vector<int32_t> calls;
		std::vector<std::vector<int32_t>> boards;
		std::vector<int32_t> board_nums;
		bool read_boards = false;
		for (const std::string& line : rx) {
			int32_t num = 0;
			if (!read_boards) {
				for (int i = 0; i < line.length(); i++) {
					char c = line[i];
					if (c == ',') {
						calls.push_back(num);
						num = 0;
					} else {
						num *= 10;
						num += (c - '0');
					}
				}
				calls.push_back(num);
				read_boards = true;
			} else {
				if (line.empty()) {
					if (!board_nums.empty()) {
						boards.push_back(board_nums);
						board_nums = std::vector<int32_t>();
					}
					continue;
				}
				bool p = false;
				for (int i = 0; i < line.length(); i++) {
					char c = line[i];
					if (c == ' ') {
						if (p) {
							board_nums.push_back(num);
						}
						num = 0;
						p = false;
					} else {
						p = true;
						num *= 10;
						num += (c - '0');
					}
				}
				board_nums.push_back(num);
			}
		}
		boards.push_back(board_nums);

		int32_t p1 = part1(calls, boards);
		printf_s("Solution 4.1: %d\n", p1);

		int32_t p2 = part2(calls, boards);
		printf_s("Solution 4.2: %d\n", p2);

		return 0;
	}
}