//
// Created by Elijah Ghossein on 5/8/25.
//

#include "Dijkstra.h"

#include <limits>
#include <queue>

std::vector<int> shortestPath(WeightedGraph graph, int start) {

    const int INF = std::numeric_limits<int>::max(); // Define a large value to represent "infinity"
    std::vector<int> cost(graph.vertices.size(), INF); // Initialize cost vector with INF for all vertices
    std::vector<int> path(graph.vertices.size(), -1); // Initialize path vector with -1 (undefined path)
    cost[start] = 0; // Set starting vertex cost to 0

    using pii = std::pair<int, int>; // Alias for a pair of (cost, vertex)
    std::priority_queue<pii, std::vector<pii>, std::greater<>> pq; // Min-heap priority queue based on cost
    pq.push({0, start}); // Start with the source vertex at cost 0

    while (!pq.empty()) { // Continue while there are vertices to process
        auto [currentCost, currentVertex] = pq.top(); // Get the vertex with the smallest cost
        pq.pop(); // Remove it from the queue

        if (currentCost > cost[currentVertex]) continue; // Skip if we've already found a better path

        for (const auto& edge : graph.vertices[currentVertex].edges) { // Examine each neighbor
            int neighbor = edge.next; // Neighbor vertex ID
            int weight = edge.weight; // Weight of the edge to the neighbor
            if (cost[currentVertex] + weight < cost[neighbor]) { // If a shorter path is found
                cost[neighbor] = cost[currentVertex] + weight; // Update the cost to reach this neighbor
                path[neighbor] = currentVertex; // Record the path
                pq.push({cost[neighbor], neighbor}); // Push updated cost and vertex to the queue
            }
        }
    }

    return path; // Return the path vector for reconstructing shortest paths
}
