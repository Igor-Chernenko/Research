#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include <optional>

struct HeapNode{
  int node_id; // v_id, index to graph vector
  long node_value; // current min distance from source to v
};

class BinaryMinHeap{
  public: 
  /**
   * Parent = floor((i-1)/2)
   * Left child = 2i+1
   * Right child = 2i+2
   */
    std::vector<HeapNode> heap;

    std::optional<HeapNode> pop_min() {
      if (heap.empty()) {
          return std::nullopt;
      }

      HeapNode min_node = heap.front();

      if (heap.size() == 1) {
          heap.pop_back();
          return min_node;
      }

      heap[0] = heap.back();
      heap.pop_back();
      bubble_down();
      return min_node;
    }

    void insert(HeapNode new_node){
      heap.push_back(new_node);
      bubble_up();
    }

    void print(){print_heap();}

  private: 
    void bubble_down(){
      int size = heap.size();
      HeapNode bubble_node = heap[0]; 
      int i = 0;

      while(2*i + 1 < size){
        int left_index = 2*i + 1;
        int right_index = 2*i + 2;
        
        int next_index = left_index; 

        if(right_index < size && heap[right_index].node_value < heap[left_index].node_value){
          next_index = right_index;
        }

        if(heap[next_index].node_value < bubble_node.node_value){
          heap[i] = heap[next_index];
          i = next_index;
        } 
        else {
          break;
        }
      }
      
      heap[i] = bubble_node;
    } 

    void bubble_up(){
      int i = heap.size()-1;
      HeapNode bubble_node = heap.back();
      
      while(i > 0){
        int parent_index = (i-1)/2;

        if(heap[parent_index].node_value > bubble_node.node_value){
          heap[i] = heap[parent_index];
          i = parent_index;
        }
        else{
          break;
        }
      }
      heap[i] = bubble_node;
    }

    void print_heap(){
      for(auto& it: heap){
        std::cout<<it.node_value<<' ';
      }
      std::cout<<'\n';
    }

};