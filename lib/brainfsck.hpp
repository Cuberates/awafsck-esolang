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
 *       - Verify file extensions [x]
 *       - Perform string parsing using std::string, but still trying to find a much quicker way to do this
 * @author Xuan Viet Duc Nguyen
 */

namespace Brainfsck {
  void run(const Program &program_, Machine &machine_); 
};

void Brainfsck::run(const Program &program, Machine &machine) { 
  /**
   * @todo Emulate Awa Brainfsck instructions HERE
   * @author Xuan Viet Duc Nguyen
  `*/ 

  std::stack<size_t> stack_loop;
  
  for(size_t i {0}; i < program.size(); i++) { 
    const Program::Instruction current_instruction = program.peek(i); 
    
    switch (current_instruction) {
      case Program::Instruction::PRINT:             break; // TODO: CALL out(machine)
      case Program::Instruction::INSTRUCTION_NULL:  break; // NOT SUPPOSED TO HAVE INSTRUCTION_NULL => HANDLE THIS ACCORDINGLY 

      case Program::Instruction::INCREMENT:         machine.increment(); break;
      case Program::Instruction::DECREMENT:         machine.decrement(); break;
      case Program::Instruction::SHIFT_PTR_LEFT:    machine.shift_left(); break;
      case Program::Instruction::SHIFT_PTR_RIGHT:   machine.shift_right();  break; 

      case Program::Instruction::BEGIN_LOOP:        stack_loop.push(i); break;  

      case Program::Instruction::END_LOOP:
        if (stack_loop.empty()) 
          throw std::runtime_error("Fatal Error: END_LOOP but stack_loop is empty. Bad syntax?");
       
        const size_t to_jump = stack_loop.top();
        Program subprogram; 
        for (size_t j {i-1}; j > to_jump; j--) {
          subprogram.push(program.peek(j));
        }        
        run(subprogram, machine);
        stack_loop.pop(); 
        break;
    }
  }  
}

#endif