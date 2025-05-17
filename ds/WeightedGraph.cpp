//
// Created by Elijah Ghossein on 5/8/25.
//

#include "WeightedGraph.h"

#include <iostream>
#include <ostream>

WeightedGraph::WeightedGraph() = default;

void WeightedGraph::addVertex() {
    vertex v;
    v.id = static_cast<int>(vertices.size());
    vertices.push_back(v);
}

void WeightedGraph::addEdge(const int from, const int to, const int weight) {
    if (from < 0 || from >= static_cast<int>(vertices.size()) ||
    to < 0 || to >= static_cast<int>(vertices.size())) {
        std::cerr << "Error in addEdge()" << std::endl;
        return;
    }
    vertices[from].edges.push_back({weight, to});
}
