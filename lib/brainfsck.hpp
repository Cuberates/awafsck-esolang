#ifndef BRAINFSCK_H
#define BRAINFSCK_H

#include <iostream>
#include <fstream>
#include <vector>  
#include <string> 
#include <stack>
#include <filesystem>

#include "../lib/program.hpp"
#include "../lib/machine.hpp"

namespace Brainfsck {
  void run(const Program &program, Machine &machine); 
};

void Brainfsck::run(const Program& program, Machine &machine) {
  std::stack<size_t> process;
  for(size_t ptr{0u} ; ptr < program.size(); true) { 
    const Program::Instruction& inst = program.peek(ptr);
    switch (inst) { 
        case Program::Instruction::INCREMENT: 
          machine.increment(); ptr++; break;
        case Program::Instruction::DECREMENT: 
          machine.decrement(); ptr++; break;
        case Program::Instruction::SHIFT_PTR_LEFT: 
          machine.shift_left(); ptr++; break; 
        case Program::Instruction::SHIFT_PTR_RIGHT: 
          machine.shift_right(); ptr++; break;
        case Program::Instruction::PRINT: 
          std::cout << machine.peek(); ptr++; break; 
        case Program::Instruction::BEGIN_LOOP: 
          process.push(ptr); ptr++; break; 
        case Program::Instruction::END_LOOP:
        
        if (process.empty()) 
          throw std::runtime_error("Error: Process stack empty upon END_LOOP call. Aborting..."); 
        
        const uint8_t& val = machine.peek();
        if (val == 0u) { process.pop(); ptr++; continue; }

        // Move the pointer back to the last BEGIN_LOOP instruction
        size_t jump_to = process.top();
        ptr = jump_to + 1;  
        break; 
    } 
  }
}

#endif
