#pragma once
#include <vector>

struct TreeNode{
  int parent;
  long cost;
};
using MinimumCostPath = std::vector<TreeNode>;

// Represents a directed, weighted connection to another vertex
struct Edge {
    int target_vertex_id;
    int weight;
};

class Graph {
public:
    // outer vector is the Vertex ID.
    // inner vector contains all outgoing edges from that Vertex.
    std::vector<std::vector<Edge>> adjacency_list;

    Graph(int num_vertices) {
        adjacency_list.resize(num_vertices);
    }

    void addEdge(int v_id, int target, int weight) {
        adjacency_list[v_id].push_back({target, weight});
    }
};
