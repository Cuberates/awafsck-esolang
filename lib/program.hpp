#ifndef PROGRAM_H
#define PROGRAM_H

#include <cstdlib> 
#include <vector>

using Instruction = uint8_t;
 
class Program { 
  public: 
  
  Program() : _inst_size(0u) {}

  void push(Instruction _inst); 
  void pop(); 
  const uint8_t& peek(); 
  size_t size(); 
  private: 
  std::vector<Instruction> _inst_list;
  size_t _inst_size; 
};


#endif