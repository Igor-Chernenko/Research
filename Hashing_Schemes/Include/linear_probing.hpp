#include <vector>
#include <optional>
#include <stdexcept>
#include <limits>
#include <cstdint>
#include <iostream>
#include <string>

typedef uint64_t ValueType;
typedef uint64_t KeyType;

enum State {Empty, Occupied, Tombstone};

struct HashNode {
    KeyType key;
    ValueType value;
    State state = Empty;
};


class OpenAddressingHashmap{
  const ValueType INVALID_VALUE = std::numeric_limits<ValueType>::max();
  const int INVALID_INDEX = -1;


  private:
    std::vector<HashNode> kv_array;
    int probe_counter = 0;
    int size;
    int occupied;

  public:

    OpenAddressingHashmap(int set_size): size(set_size), occupied(0){
      kv_array.resize(size);// ignore resize cost
    };
  
    void Insert(KeyType k, ValueType v){
      if(occupied == size){ throw std::runtime_error("Table is full"); }

      HashNode new_hash_node{k,v, State::Occupied};

      std::hash<KeyType> hash;
      int start = hash(k) % size;
      int index = start;
      int first_deleted_index = INVALID_INDEX;

      while(kv_array[index].state != State::Empty){ 
        probe_counter++;

        if(kv_array[index].state == State::Tombstone && first_deleted_index == INVALID_INDEX){
          first_deleted_index = index;
        }

        if(kv_array[index].key == k && kv_array[index].state == State::Occupied){//duplicate
          kv_array[index].value = v;
          return;
        }
        index = (index + 1) % size; 
        if(index == start){ break; }//not found
      }
      probe_counter++;
      //either go to the tombstone index if one is found
      //or insert at the end if no tombstone found
      if(first_deleted_index != INVALID_INDEX){
        kv_array[first_deleted_index] = new_hash_node;
      }else{
        kv_array[index] = new_hash_node;
      }
      occupied += 1;

      return;
    }

    ValueType Find(KeyType k){
      std::hash<KeyType> hash;
      int start = hash(k) % size;
      int index = start;

      while(kv_array[index].state != State::Empty){
        probe_counter++;
        if(kv_array[index].key == k){
          if(kv_array[index].state == State::Tombstone){return INVALID_VALUE;}
          return kv_array[index].value;
        }
        index = (index + 1) % size;
        if(index == start){
          return INVALID_VALUE;
        }
      }
      probe_counter++;
      return INVALID_VALUE;
    }

    int GetProbeCount(){
      int val = probe_counter;
      return val;
    }
};