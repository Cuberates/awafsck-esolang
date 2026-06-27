#ifndef MACHINE_H
#define MACHINE_H

#include <array> 
#include <iostream>
#include <cstdint>
#include <string> 
#include <limits>

#define REGISTER_CAPACITY_MAX 16

using Register = std::array<uint8_t, REGISTER_CAPACITY_MAX>; 

/**
 * @brief Machine API for emulating a one-dimensional tape of memory cells used in BF esolang
 * @author Xuan Viet Duc Nguyen
*/
class Machine {
  private: 
  Register _register; 
  size_t _pos;  

  public:
  Machine(); 
  Machine(const uint8_t& _initial_val);
  
  void increment(); 
  void decrement(); 
  void shift_left();
  void shift_right();

  friend void out(const Machine& _machine);

  [[nodiscard]]
  const size_t& get_pos() const;              // Returning the current position of the pointer 
  [[nodiscard]]
  const uint8_t& peek() const;                // Returning the value of the cell being pointed;  
  const uint8_t& peek(size_t pos) const; 
};

/**
 * @brief Machine API implementation, perform on std::array
 * @author Xuan Viet Duc Nguyen
 */

Machine::Machine(const uint8_t& _initial_val) : _pos(0u) { 
  _register.fill(_initial_val);
}
Machine::Machine() : Machine(0u) {}

void Machine::shift_right() {  
  _pos = (_pos == (REGISTER_CAPACITY_MAX - 1) ? 0 : _pos + 1);  
}

void Machine::shift_left() {
  _pos = (_pos == 0 ? (REGISTER_CAPACITY_MAX - 1) : _pos - 1); 
}

void Machine::increment() { 
  auto &val = *(_register.begin() + _pos); 
  val = (val == std::numeric_limits<uint8_t>::max() ? 0 : val + 1);
}

void Machine::decrement() { 
  auto &val = *(_register.begin() + _pos);
  val = (val == 0 ? std::numeric_limits<uint8_t>::max() : val - 1);
}

const size_t& Machine::get_pos() const { 
  return _pos;
}

const uint8_t& Machine::peek() const { 
  return *(_register.begin() + _pos);
}
const uint8_t& Machine::peek(size_t pos) const { 
   return * (_register.begin() + pos);
}

void out(const Machine& _machine) { 
  for(size_t cell{0}; cell < REGISTER_CAPACITY_MAX; ++cell) { 
  std::cout << cell << "\t" << static_cast<unsigned>(_machine._register[cell]) << "\t"; 
    if (cell == _machine._pos) std::cout << "*"; 
    std::cout << std::endl; 
  }
}

#endif 