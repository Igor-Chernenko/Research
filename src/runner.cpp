#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "linear_probing.hpp"
#include "chaining.hpp"

int main() {
  std::string path = "./Tests/case_M200000_N180000_alpha0.9.txt";
  std::ifstream in(path);
  if (!in) return 1;

  int M;
  in >> M;
  std::string line;
  std::getline(in, line);

  OpenAddressingHashmap oa(M);
  ChainingHashmap ch(M);

  while (std::getline(in, line)) {
    if (line.empty()) continue;
    std::istringstream ss(line);
    char op;
    ss >> op;

    if (op == 'I') {
      KeyType k; ValueType v;
      ss >> k >> v;
      oa.Insert(k, v);
      ch.Insert(k, v);
    } else if (op == 'F') {
      KeyType k;
      ss >> k;
      oa.Find(k);
      ch.Find(k);
    } else if (op == 'R') {
      std::cout <<"Linear Probing Probe Count: "<< oa.GetProbeCount() << "\nChaining Probe Count: " << ch.GetProbeCount() << "\n";
    }else if (op == '#') {
      std::cout << line << std::endl;
    }
  }

  return 0;
}

//run with: g++ -std=c++20 runner.cpp -o runner