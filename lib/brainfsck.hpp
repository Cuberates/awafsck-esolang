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
  void verify(const std::filesystem::path& file_path);
  void parse(Program &program_, std::ifstream& source_file);
  void run(const Program &program_, Machine &machine_); 
};

void Brainfsck::verify(const std::filesystem::path& file_path) { 
  if (file_path.extension() != ".awa") 
    throw std::runtime_error("Cannot recognize .awa file extension!"); 
} 

void Brainfsck::parse(Program &program_, std::ifstream& source_file) {
  std::vector<std::string> lines; 

  /**
   * @bug Performance: Passing all entries from source_file into a std::vector and then process them later 
   * @todo Create a stack frame?  
   * @todo Process each line entry, but the following parser model works? 
   * @author Xuan Viet Duc Nguyen
   */
  std::string line;
  while (std::getline(source_file, line)) {
    lines.push_back(line); // Perfomance issue

    if (!source_file.eof()) {
      lines.push_back("\n");
    }
  }
  for(size_t l{0}; l < lines.size(); l++) {
    std::cout << lines[l] << "\n";
  }
}

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