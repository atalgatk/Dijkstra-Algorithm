#ifndef BETTERPRIORITYQUEUE_H
#define BETTERPRIORITYQUEUE_H

#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// This is a "Dijkstra Node" it is used for the Dijkstra algorithm
// and it is used as the items in the BetterPriorityQueue
struct DNode
{
    int pri = INT_MAX;
    bool visited = false;
    const GraphNode *node = nullptr;

    bool operator<(const DNode &other) const
    {
        return pri < other.pri;
    }

    bool operator>(const DNode &other) const
    {
        return pri > other.pri;
    }

    bool operator==(const DNode &other) const
    {
        return node->key == other.node->key;
    }
};

class BetterPriorityQueue : public priority_queue<DNode, vector<DNode>,
                                                  greater<DNode>>::priority_queue
{
public:
    bool Contains(DNode dn);
    bool Update(DNode dn);
    string ToString();
    string DnodeToString(DNode dn);
};
#endif