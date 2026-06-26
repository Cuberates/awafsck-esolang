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

/**
 * @brief Complete file parser and code execution for organizing Awa syntaxes
 * @todo - Parse commands into program_ object 
 *       - Perform string parsing using std::string, but still trying to find a much quicker way to do this
 * @author Xuan Viet Duc Nguyen
 */

namespace Brainfsck {
  void run(const Program &program, Machine &machine); 
};

/**
*  @todo Emulate Awa Brainfsck instructions HERE
*  @author Xuan Viet Duc Nguyen
*/

void Brainfsck::run(const Program& program, Machine &machine) { 
   std::stack<Program::Instruction> program_stack; 
   for (size_t p {0}; p < program.size(); ++p) { 
      Program::Instruction inst = program.peek(p); 
      if (inst != Program::Instruction::END_LOOP) { 
         program_stack.push(inst); 
         continue; 
      }
      // pop until we detect BEGIN_LOOP; store intermediate values in the buffer;
      std::stack<Program::Instruction> buffer;
      //std::stack<Program::Instruction> cpy_buffer = buffer; 
      
      bool found_begin = false; 

      while (program_stack.empty() == false) { 
         Program::Instruction lst = program_stack.top(); 
         program_stack.pop(); 
         if (lst == Program::Instruction::BEGIN_LOOP) { 
            found_begin = true; 
            break; 
         }
         buffer.push(lst);
      }
      std::stack<Program::Instruction> cpy_buffer = buffer;  
      if (!found_begin) 
         throw std::runtime_error("Error: Cannot locate BEGIN_LOOP instruction!");
      
      while (!buffer.empty()) { 
         Program::Instruction lst = buffer.top();
         buffer.pop();
         program_stack.push(lst);
      } 
      
      while (!cpy_buffer.empty()) { 
         Program::Instruction lst = cpy_buffer.top(); 
         cpy_buffer.pop(); 
         program_stack.push(lst); 
      }
   }
   std::stack<Program::Instruction> exec; 

   while (!program_stack.empty()) { 
      Program::Instruction inst = program_stack.top(); 
      program_stack.pop();
      exec.push(inst);
   }
   while (!exec.empty()) { 
      Program::Instruction inst = exec.top(); 
      exec.pop(); 
      switch (inst) { 
         case Program::Instruction::INCREMENT:
            machine.increment(); break; 
         case Program::Instruction::DECREMENT: 
            machine.decrement(); break; 
         case Program::Instruction::SHIFT_PTR_LEFT:
            machine.shift_left(); break; 
         case Program::Instruction::SHIFT_PTR_RIGHT: 
            machine.shift_right(); break; 
      }
   }
}

#endif
