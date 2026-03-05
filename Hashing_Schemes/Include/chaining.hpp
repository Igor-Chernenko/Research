#include <vector>
#include <optional>
#include <stdexcept>
#include <limits>
#include <cstdint>
#include <iostream>
#include <string>

typedef uint64_t ValueType;
typedef uint64_t KeyType;

struct Node{
  KeyType key;
  ValueType value;
  std::optional<Node*> next_node;
};

class ChainingHashmap{
  const ValueType INVALID_VALUE = std::numeric_limits<ValueType>::max();


  private:
    std::vector<std::optional<Node>> kv_array;
    int probe_counter = 0;
    int size;

  public:

    ChainingHashmap(int set_size): size(set_size){
      kv_array.resize(size);// ignore resize cost
    };
  
    void Insert(KeyType k, ValueType v){ 

      Node new_pair{k,v};
      std::hash<KeyType> hash;
      int index = hash(k) % size;

      probe_counter++;
      if(!kv_array[index].has_value()){
        kv_array[index] = new_pair;
        return;
      }

      Node* it = &kv_array[index].value();
      probe_counter++;
      if(it->key == k){return;}//duplicate

      while(it->next_node.has_value()){
        it = it->next_node.value();
        probe_counter++;
        if(it->key == k){
          return;} //duplicate
      }
      it->next_node = new Node{k,v};
      return;
    }

    ValueType Find(KeyType k){
      std::hash<KeyType> hash;
      int index = hash(k) % size;
      probe_counter++;
      if(!kv_array[index].has_value()){
        return INVALID_VALUE;
      }

      Node* it = &kv_array[index].value();
      while(it->key != k){
        probe_counter++;
        if(!it->next_node.has_value()){return INVALID_VALUE;}
        it = it->next_node.value();
      }
      probe_counter++;
      return it->value;
    }

    int GetProbeCount(){
      int val = probe_counter;
      return val;
    }

};