#pragma once
#include "graph.hpp"
#include "heap.hpp"
#include <limits>
#include <chrono>

/**
 *  adapted from "Algorithm Science (Summer 2025) - 35 - Minimum Cost Paths II" 
 *  by Bill Bird on YouTube
 */

const int INVALID_NEIGHBOUR = -1;

class MinHeapDijkstra {
public:
  std::vector<MinimumCostPath> result;

  MinHeapDijkstra(const Graph& G, std::vector<int> S) {
    for(auto& S_i: S){
      result.push_back(execute(G, S_i));
    }
  }

  MinimumCostPath execute(const Graph& G, int source_vertex_ind) {
    int num_vertices = G.adjacency_list.size();
    MinimumCostPath min_cost_path(num_vertices, {INVALID_NEIGHBOUR, inf});
    min_cost_path[source_vertex_ind].cost = 0;

    BinaryMinHeap heap;
    heap.insert({source_vertex_ind, 0});

    for(int i = 0; i < num_vertices; i++) {
      if(i != source_vertex_ind) {
        heap.insert({i, inf});
      }
    }

    int tree_vertices = 0;

    while(tree_vertices < num_vertices && !heap.heap.empty()) {
      std::optional<HeapNode> u_opt = heap.pop_min();
      
      if(!u_opt.has_value() || u_opt.value().node_value == inf) {
        break;
      }

      HeapNode u = u_opt.value();

      if (u.node_value > min_cost_path[u.node_id].cost) {
        continue;
      }

      tree_vertices++;

      for(auto& edge : G.adjacency_list[u.node_id]) {
        relax_edge(u.node_id, edge, min_cost_path, heap);
      }
    }
    
    return min_cost_path;
  }

private:
  void relax_edge(int u, auto& edge, MinimumCostPath& min_cost_path, BinaryMinHeap& heap) {
    int v = edge.target_vertex_id;
    long weight = edge.weight;

    if(min_cost_path[u].cost + weight < min_cost_path[v].cost) {
      min_cost_path[v].parent = u;
      min_cost_path[v].cost = min_cost_path[u].cost + weight;
      heap.insert({v, min_cost_path[v].cost});
    }
  }
};