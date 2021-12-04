#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
#include <string>

namespace aoc {

	void ReadFromFile(std::vector<int32_t>& x, const std::string& file_name);

	void ReadFromFile(std::vector<std::string>& x, const std::string& file_name);

}