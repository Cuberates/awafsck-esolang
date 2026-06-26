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


TEST(brainfscks, single_static_for_loop) { 
  // Construct a program idk why I am using pointer
  Program *test_program = new Program(); 
  Machine *test_machine = new Machine(static_cast<uint8_t>(0u));

  const std::array<Program::Instruction, 6> instructions {
    Program::Instruction::BEGIN_LOOP, 
    Program::Instruction::BEGIN_LOOP, // 
    Program::Instruction::INCREMENT, // Increment cell 0 by 0 (twice) => 2
    Program::Instruction::END_LOOP,
    Program::Instruction::END_LOOP, // Increment cell 0 by 0 => 4 
    Program::Instruction::SHIFT_PTR_RIGHT, // Pointer should be in cell 1
  };

  for(size_t i {0}; i < instructions.size(); i++) { 
    test_program->push(instructions[i]); 
  }
 
  Brainfsck::run(*test_program, *test_machine);
  out(*test_machine);

  free(test_program);
  free(test_machine);
}

int main(void) { 
  ::testing::InitGoogleTest(); 
  return RUN_ALL_TESTS();   
}
