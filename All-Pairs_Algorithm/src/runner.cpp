#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "graph.hpp"
#include "FWR.hpp"
#include "dijkstra.hpp"

std::string FILENAME = "./Tests/test_case_V50";

struct EdgeInput {
    int u;
    int v;
    long w;
};

//This function checks if the results from Floyd-Warshall-ROy and Dijkstra are the same
bool same_costs(const std::vector<MinimumCostPath>& floyd_res, const std::vector<MinimumCostPath>& dijkstra_res) {
    if (floyd_res.size() != dijkstra_res.size()) {
        return false;
    }
    for (int i = 0; i < (int)floyd_res.size(); i++) {
        if (floyd_res[i].size() != dijkstra_res[i].size()) {
            return false;
        }

        //compare each individual destination cost
        for (int j = 0; j < (int)floyd_res[i].size(); j++) {
            if (floyd_res[i][j].cost != dijkstra_res[i][j].cost) {
                return false;
            }
        }
    }
    return true;
}

int main() {
  int repeats = 25;

  std::ifstream inputFile(FILENAME);
  if (inputFile.is_open() == false) {
      std::cout << "Error: Could not open the file " << FILENAME << std::endl;
      return 1;
  }

  std::ofstream outputFile("results.csv");
  if (outputFile.is_open() == false) {
      std::cout << "Error: Could not create the output file results.csv" << std::endl;
      return 1;
  }

  int num_vertices = 0;
  std::vector<EdgeInput> edges;
  std::vector<int> sources;
  int case_num = 1;
  outputFile << "V,E,k,floyd_ms,dijkstra_ms,valid\n";

  std::string line;
  while (std::getline(inputFile, line)) {

    if (line.empty()) {
      continue;
    }

    // comment
    if (line[0] == '#') {
      continue;
    }

    std::istringstream ss(line);
    std::string command;
    ss >> command;
    
    // "R" resets everything to do more tests
    if (command == "R") {
      num_vertices = 0;
      edges.clear();
      sources.clear();
    }

    // "N" sets the number of vertices
    if (command == "N") {
      ss >> num_vertices;
    }
    // "E" adds an edge(from, to, weight)
    else if (command == "E") {
      EdgeInput new_edge;
      ss >> new_edge.u >> new_edge.v >> new_edge.w;
      edges.push_back(new_edge);
    }
    // "S" adds a source vertex to search from
    else if (command == "S") {
      int s;
      ss >> s;
      sources.push_back(s);
    }
    // "RUN" means process the graph we just built
    else if (command == "RUN") {
      Graph G(num_vertices);
      for (int i = 0; i < (int)edges.size(); i++) {
        G.addEdge(edges[i].u, edges[i].v, edges[i].w);
      }

      double floyd_total_time = 0.0;
      double dijkstra_total_time = 0.0;

      std::vector<MinimumCostPath> floyd_result;
      std::vector<MinimumCostPath> dijkstra_result;

      //run the algorithms multiple times to get an average speed
      for (int i = 0; i < repeats; i++) {
        // time the Floyd-Warshall-Roy algorithm
        auto start1 = std::chrono::steady_clock::now();
        FloydWarshallRoy fw(G, sources);
        auto end1 = std::chrono::steady_clock::now();

        // time the Dijkstra algorithm
        auto start2 = std::chrono::steady_clock::now();
        MinHeapDijkstra dj(G, sources);
        auto end2 = std::chrono::steady_clock::now();

        std::chrono::duration<double, std::milli> diff1 = end1 - start1;
        std::chrono::duration<double, std::milli> diff2 = end2 - start2;

        floyd_total_time = floyd_total_time + diff1.count();
        dijkstra_total_time = dijkstra_total_time + diff2.count();

        if (i == 0) {
          floyd_result = fw.result;
          dijkstra_result = dj.result;
        }
      }

      double floyd_avg = floyd_total_time / repeats;
      double dijkstra_avg = dijkstra_total_time / repeats;
      bool isValid = same_costs(floyd_result, dijkstra_result);

      outputFile << num_vertices << "," 
                 << edges.size() << "," 
                 << sources.size() << "," 
                 << floyd_avg << "," 
                 << dijkstra_avg << "," 
                 << (isValid ? "yes" : "no") << "\n";
    }
  }
  inputFile.close();
  outputFile.close(); 
  
  return 0;
}