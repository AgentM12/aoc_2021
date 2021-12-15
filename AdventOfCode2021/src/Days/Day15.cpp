#include <iostream>
#include <vector>
#include <iterator>
#include <queue>
#include "../AdventOfCode2021.hpp"

namespace Day15 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day15_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day15_test_input.txt";

	struct Vertex {
		int32_t dist;
		uint8_t w;
		std::vector<std::shared_ptr<Vertex>> adj;

		Vertex() : dist(INT32_MAX), w(0) {}

		Vertex(uint8_t w)
			: dist(INT32_MAX), w(w) {}

	};

	class CompareVertices {
	public:
		// Reverse direction
		bool operator()(const std::shared_ptr<Vertex>& a, const std::shared_ptr<Vertex>& b) const {
			return a->dist > b->dist;
		}
	};

	int32_t dijkstra(std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end) {
		std::priority_queue<std::shared_ptr<Vertex>, std::vector<std::shared_ptr<Vertex>>, CompareVertices> pq;
		pq.emplace(start);
		start->dist = 0;
		int i = 0;
		while (!pq.empty()) {
			++i;
			std::shared_ptr<Vertex> v = pq.top();
			pq.pop();
			for (std::shared_ptr<Vertex> w : v->adj) {
				if (v->dist + w->w < w->dist) {
					w->dist = v->dist + w->w;
					pq.emplace(w);
				}
			}
		}
		return end->dist;
	}

	int32_t part1(const std::vector<std::string>& input) {
		std::shared_ptr<Vertex> start, end;
		size_t w = input[0].length(), h = input.size();
		std::vector<std::shared_ptr<Vertex>> vertices;
		for (size_t y = 0; y < h; y++) {
			const std::string& line = input[y];
			for (size_t x = 0; x < w; x++) {
				std::shared_ptr<Vertex> v = std::make_shared<Vertex>(Vertex(line[x] - '0'));
				if (x > 0) {
					v->adj.push_back(vertices[vertices.size() - 1]);
					vertices[vertices.size() - 1]->adj.push_back(v);
				}
				if (y > 0) {
					v->adj.push_back(vertices[(y - 1) * w + x]);
					vertices[(y - 1) * w + x]->adj.push_back(v);
				}
				if (x == 0 && y == 0) start = v;
				if (x == (w - 1) && y == (h - 1)) end = v;
				vertices.push_back(v);
			}
		}
		return dijkstra(start, end);
	}

	int32_t part2(const std::vector<std::string>& input) {
		std::shared_ptr<Vertex> start, end;
		size_t w = input[0].length(), h = input.size();
		size_t w2 = input[0].length() * 5, h2 = input.size() * 5;
		std::vector<std::shared_ptr<Vertex>> vertices;
		for (size_t y = 0; y < h2; y++) {
			const std::string& line = input[y % h];
			for (size_t x = 0; x < w2; x++) {
				std::shared_ptr<Vertex> v = std::make_shared<Vertex>(Vertex(1 + ((line[x % w] - '0') - 1 + (y / h) + (x / w)) % 9));
				if (x > 0) {
					v->adj.push_back(vertices[vertices.size() - 1]);
					vertices[vertices.size() - 1]->adj.push_back(v);
				}
				if (y > 0) {
					v->adj.push_back(vertices[(y - 1) * w2 + x]);
					vertices[(y - 1) * w2 + x]->adj.push_back(v);
				}
				if (x == 0 && y == 0) start = v;
				if (x == (w2 - 1) && y == (h2 - 1)) end = v;
				vertices.push_back(v);
			}
		}
		return dijkstra(start, end);
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		int32_t p1 = part1(rx);
		printf_s("Solution 15.1: %d\n", p1);

		int32_t p2 = part2(rx);
		printf_s("Solution 15.2: %d\n", p2);

		return 0;
	}
}