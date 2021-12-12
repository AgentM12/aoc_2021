#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>
#include <iterator>
#include <chrono>
#include "../AdventOfCode2021.hpp"

namespace Day12 {
	constexpr bool TEST = false;

	constexpr auto INPUT_FILE_PATH = "data/day12_input.txt";
	constexpr auto TEST_INPUT_FILE_PATH = "data/day12_test_input.txt";

	struct Node {
		std::string name;
		std::vector<std::shared_ptr<Node>> neighbors;

		Node(std::string name)
			: name(name) {}

		void AddNeighbor(std::shared_ptr<Node> node) {
			neighbors.push_back(node);
		}
	};

	class Walker {
	private:
		std::shared_ptr<Node> m_Node;
		std::vector<std::shared_ptr<Node>> m_Visited;
		std::vector<std::shared_ptr<Node>> m_Path;
		bool m_HasSkip;
	public:
		Walker(const std::shared_ptr<Node>& node, bool hasSkip)
			: m_Node(node), m_Visited(), m_Path(), m_HasSkip(hasSkip) {}

		Walker(const std::shared_ptr<Node>& node, std::vector<std::shared_ptr<Node>> visited, std::vector<std::shared_ptr<Node>> path, bool hasSkip)
			: m_Node(node), m_Visited(visited), m_Path(path), m_HasSkip(hasSkip) {}

		~Walker() {}

		void Walk(std::vector<Walker>& walkers) {

			m_Path.push_back(m_Node);
			if (m_Node->name == "end") return;
			if (!isupper(m_Node->name[0])) {
				m_Visited.push_back(m_Node);
			}

			for (const std::shared_ptr<Node>& n : m_Node->neighbors) {
				if (std::find(m_Visited.begin(), m_Visited.end(), n) != m_Visited.end()) {
					if (m_HasSkip && n->name != "start") {
						walkers.push_back(Walker(n, m_Visited, m_Path, false));
					}
					continue;
				}
				walkers.push_back(Walker(n, m_Visited, m_Path, m_HasSkip));
			}
		}

		std::shared_ptr<Node>& GetNode() {
			return m_Node;
		}
	};

	int32_t bfs(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& end, bool part2 = false) {
		std::vector<Walker> walkers;
		walkers.push_back(Walker(start, part2));
		int32_t pathCount = 0;
		while (!walkers.empty()) {
			std::vector<Walker> newWalkers;
			for (Walker& w : walkers) {
				w.Walk(newWalkers);
				if (w.GetNode() == end) ++pathCount;
			}
			walkers = newWalkers;
		}
		return pathCount;
	}

	int32_t part1(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& end) {
		return bfs(start, end);
	}

	int32_t part2(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& end) {
		return bfs(start, end, true);
	}

	int run() {
		std::vector<std::string> rx;
		if (TEST) {
			aoc::ReadFromFile(rx, TEST_INPUT_FILE_PATH);
		} else {
			aoc::ReadFromFile(rx, INPUT_FILE_PATH);
		}

		std::shared_ptr<Node> start, end;
		std::unordered_map<std::string, std::shared_ptr<Node>> graph;

		for (const std::string& line : rx) {
			size_t i = line.find('-');
			std::array<std::string, 2> nodeNamePair{line.substr(0, i), line.substr(i + 1, line.size())};
			std::array<std::shared_ptr<Node>, 2> nodePair;
			bool second = false;
			for (const std::string& x : nodeNamePair) {
				std::shared_ptr<Node> node_x;
				auto cond_x = graph.find(x);
				if (cond_x != graph.end()) {
					node_x = cond_x->second;
				} else {
					node_x = std::make_shared<Node>(Node(x));
					if (x == "start") {
						start = node_x;
					} else if (x == "end") {
						end = node_x;
					}
				}
				graph[x] = node_x;
				nodePair[second] = node_x;
				second = true;
			}
			nodePair[0]->AddNeighbor(nodePair[1]);
			nodePair[1]->AddNeighbor(nodePair[0]);
		}

		auto start1 = std::chrono::high_resolution_clock::now();
		int32_t p1 = part1(start, end);
		auto stop1 = std::chrono::high_resolution_clock::now();
		auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
		printf_s("Solution 12.1: %d [%lld ms]\n", p1, duration1.count());

		//printf_s("Solution 12.1: %d\n", p1);

		auto start2 = std::chrono::high_resolution_clock::now();
		int32_t p2 = part2(start, end);
		auto stop2 = std::chrono::high_resolution_clock::now();
		auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);
		printf_s("Solution 12.2: %d [%lld ms]\n", p2, duration2.count());

		//printf_s("Solution 12.2: %d\n", p2);
		return 0;
	}
}
