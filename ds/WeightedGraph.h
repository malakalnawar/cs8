//
// Created by Elijah Ghossein on 5/8/25.
//

#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
#include <set>

class WeightedGraph {

public:

    struct edge {
        int weight;
        int next;
    };
    struct vertex {
        int id;
        std::vector<edge> edges;
        bool operator<(const vertex& other) const {
            return id < other.id;
        }
    };

    WeightedGraph();

    void addVertex();
    void addEdge(int from, int to, int weight);

    std::vector<vertex> vertices;

};



#endif //WEIGHTEDGRAPH_H
