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
   for(size_t ptr {0}; ptr < program.size(); ptr++) { 
      const Program::Instruction& inst = program.peek(ptr);
      switch (inst) { 
         case Program::Instruction::INCREMENT: machine.increment(); break;
         case Program::Instruction::DECREMENT: machine.decrement(); break;
         case Program::Instruction::SHIFT_PTR_LEFT: machine.shift_left(); break; 
         case Program::Instruction::SHIFT_PTR_RIGHT: machine.shift_right(); break;
         case Program::Instruction::BEGIN_LOOP: process.push(ptr); break; 

         case Program::Instruction::END_LOOP:
         
         if (process.empty()) 
            throw std::runtime_error("Error: Process stack empty upon END_LOOP call. Aborting..."); 
         
         const uint8_t& val = machine.peek();
         if (val == 0u) { process.pop(); continue; }

         // Move the pointer back to the last BEGIN_LOOP instruction
         size_t jump_to = process.top();
         ptr = jump_to; 
         
         break; 
      } 
   }
}

#endif
