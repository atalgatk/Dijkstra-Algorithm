#include <iostream>
#include <climits>

#define nodekey_t unsigned long long int
#define INVALID_NODE_KEY ULLONG_MAX

// BPQNode struct represents a node in the priority queue used for Dijkstra's algorithm.
struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;
	
	bool operator<(const BPQNode &other) const {
		return pri < other.pri;
	}

	bool operator>(const BPQNode &other) const {
		return pri > other.pri;
	}
	
	bool operator==(const BPQNode &other) const {
		return this->gnode == other.gnode;
	}
};