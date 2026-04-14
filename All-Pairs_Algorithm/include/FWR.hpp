#pragma once
#include "graph.hpp"
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>

/**
 *  adapted from "Algorithm Science (Summer 2025) - 36 - Minimum Cost Paths III" 
 *  by Bill Bird on YouTube
 */

long inf = std::numeric_limits<long>::max();

class FloydWarshallRoy {
public:
  std::vector<MinimumCostPath> result;

  FloydWarshallRoy(const Graph& G, std::vector<int> S) {
    int n = G.adjacency_list.size();
    
    std::vector<std::vector<long>> cost(n, std::vector<long>(n, inf));
    std::vector<std::vector<int>> parent(n, std::vector<int>(n, -1)); 
    
    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < n; i++) {
      cost[i][i] = 0;
    }

    for(int i = 0; i < n; i++) {
      for(const Edge& edge : G.adjacency_list[i]) {
        cost[i][edge.target_vertex_id] = edge.weight;
        parent[i][edge.target_vertex_id] = i; 
      }
    }
    for(int k = 0; k < n; k++) {
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
          if (cost[i][k] != inf && cost[k][j] != inf) {
            if (cost[i][k] + cost[k][j] < cost[i][j]) {
              cost[i][j] = cost[i][k] + cost[k][j];
              parent[i][j] = parent[k][j]; 
            }
          }
        }
      }
    }
    for (int source : S) {
      MinimumCostPath path_for_source(n);
      for (int v = 0; v < n; v++) {
        path_for_source[v].cost = cost[source][v];
        path_for_source[v].parent = parent[source][v];
      }
      result.push_back(path_for_source);
    }
  }
};
