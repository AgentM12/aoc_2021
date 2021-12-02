#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>

namespace aoc {

	template <typename T>
	void ReadFromFile(std::vector<T>& x, const std::string& file_name) {
		std::ifstream read_file(file_name);
		if (read_file.is_open()) {

			std::copy(std::istream_iterator<T>(read_file), std::istream_iterator<T>(),
					  std::back_inserter(x));

			read_file.close();
		}
	}

}