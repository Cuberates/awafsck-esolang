#ifndef PROGRAM_H
#define PROGRAM_H

#include <cstdlib> 
#include <vector>

/**
 * @brief Program acts as a queue that contains atomic instructions for interacting with Machine
 * @author Xuan Viet Duc Nguyen
 * @todo Implement complete queue structure using std::vector, with fast pop() 
 *  */ 

class Program { 
  public: 
  enum class Instruction { 
    INCREMENT, 
    DECREMENT, 
    SHIFT_PTR_LEFT, 
    SHIFT_PTR_RIGHT, 
    INSTRUCTION_NULL, 
  };

  Program();
  [[nodiscard]]
  const size_t size() const; 
  [[nodiscard]]
  const Instruction& peek() const;
  const Instruction& peek(size_t _pos) const; 
  
  void push(Instruction _inst);
  
  private:
  size_t _inst_capacity; 
  size_t _inst_end;
  std::vector<Instruction> _inst_list;
};

Program::Program() : 
  _inst_capacity{1024u}, 
  _inst_end{0}, 
  _inst_list{std::vector<Instruction>(_inst_capacity)} 
{}

void Program::push(Instruction _inst) {   
  if (_inst == Program::Instruction::INSTRUCTION_NULL)
    throw std::runtime_error("push() called on NULL instruction"); 

  _inst_list[_inst_end++] = _inst; 

  if (_inst_end >= _inst_capacity) {
    _inst_capacity *= 2;  
    _inst_list.resize(_inst_capacity);
  }  
}

const size_t Program::size() const { 
  return _inst_end;
}

const Program::Instruction& Program::peek() const { 
  if (!size()) 
    throw std::runtime_error("peek() called on empty instruction list?");
  return _inst_list[_inst_end - 1]; 
} 

const Program::Instruction& Program::peek(size_t _pos) const { 
  if (_pos >= _inst_end)
    throw std::runtime_error("peek() called on parameter _pos exceeding _inst_end");
  return _inst_list[_pos];
}

#endif