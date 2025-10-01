#include <queue>
#include <iostream>
#include "Dijkstra.h"
#include "BetterPriorityQueue.h"

using namespace std;

//this function implements Dijkstra's algorithm to find the shortest path between 'start' and 'end' nodes in graph 'g'
int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    if (!g->IsPresent(start) || !g->IsPresent(end)) {
        throw invalid_argument("Start or end node not present in the graph");
    }

    BetterPriorityQueue pq;
    //here we use large initial values (UINT_MAX) as placeholders for infinity.
    vector<int> costs;

    for (size_t i = 0; i < g->GetNodes().size(); i++) {
        costs[i] = UINT_MAX;
    }

    //start by setting the initial node with priority 0, since the distance from 'start' to itself is zero.
    BPQNode node;
    node.gnode = start;
    node.pri = 0;
    pq.push(node);

    while (!pq.empty()) {
        BPQNode current = pq.top();
        pq.pop();

        //if the curr node is the destination, we've found the shortest path.
        if (current.gnode == end) {
            break;
        }

        //we check each outward edge from the curr node here and calculate potential new paths through neighboring nodes.
        for (const GraphEdge *edge : g->GetOutwardEdgesFrom(current.gnode)) {
            unsigned int new_distance = costs[current.gnode] + edge->weight;

            //if this new path is shorter, then we need to update the cost and add the node to the queue.
            if (new_distance < size_t(costs[edge->to])) {
                costs[edge->to] = new_distance;
                BPQNode node1;
                node.gnode = edge->to;
                node.pri = new_distance;
                pq.push(node1);
            }
        }
    }
    //if the node is unreachable, 'costs[end]' will remain UINT_MAX.
    return costs[end];
};