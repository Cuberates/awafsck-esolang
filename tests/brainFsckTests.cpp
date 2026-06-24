/**
 * @brief Test suites for Brainfsck 
 * @author Xuan Viet Duc Nguyen   
 * @attention @todo Find a way to verify final state of Machine
 */

#include "../lib/brainfsck.hpp"
#include "../lib/program.hpp"
#include "../lib/machine.hpp"

#include <iostream>
#include <gtest/gtest.h>

TEST(brainfsck, execute_program) { 
  // Construct a program idk why I am using pointer
  Program *test_program = new Program(); 
  Machine *test_machine = new Machine(static_cast<uint8_t>(0u));

  const std::array<Program::Instruction, 5> instructions {
    Program::Instruction::SHIFT_PTR_RIGHT, // Pointer is now on cell 1
    Program::Instruction::BEGIN_LOOP, // Start loop
    Program::Instruction::INCREMENT, // Increment cell 1 by 1 (twice)
    Program::Instruction::END_LOOP,
    Program::Instruction::PRINT, // Currently does nothing
  };

  for(size_t i {0}; i < instructions.size(); i++) { 
    test_program->push(instructions[i]); 
  }
 
  Brainfsck::run(*test_program, *test_machine);
  // out(*test_machine);  


  free(test_program);
  free(test_machine);
}

int main(void) { 
  ::testing::InitGoogleTest(); 
  return RUN_ALL_TESTS();   
}