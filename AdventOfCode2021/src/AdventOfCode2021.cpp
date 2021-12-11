
#include "Days.hpp"
#include "AdventOfCode2021.hpp"

namespace aoc {
	
	void ReadFromFile(std::vector<int32_t>& x, const std::string& file_name) {
		std::ifstream read_file(file_name);
		if (read_file.is_open()) {

			std::copy(std::istream_iterator<int32_t>(read_file), std::istream_iterator<int32_t>(),
					  std::back_inserter(x));

			read_file.close();
		}
	}

	void ReadFromFile(std::vector<std::string>& x, const std::string& file_name) {
		std::ifstream read_file(file_name);
		if (read_file.is_open()) {
			std::string line;
			while (std::getline(read_file, line)) {
				x.push_back(line);
			}
		}
	}
}

int main() {

	Day1::run();
	Day2::run();
	Day3::run();
	Day4::run();
	Day5::run();
	Day6::run();
	Day7::run();
	Day8::run();
	Day9::run();
	Day10::run();
	Day11::run();
	//Day12::run();
	//Day13::run();
	//Day14::run();
	//Day15::run();
	//Day16::run();
	//Day17::run();
	//Day18::run();
	//Day19::run();
	//Day20::run();
	//Day21::run();
	//Day22::run();
	//Day23::run();
	//Day24::run();
	//Day25::run();

	return 0;
}