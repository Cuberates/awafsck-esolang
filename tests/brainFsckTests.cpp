/**
 * @brief Test suites for Brainfsck
 * @author Xuan Viet Duc Nguyen
 */

#include "../lib/brainfsck.hpp"
#include "../lib/program.hpp"
#include "../lib/machine.hpp"

#include <array>
#include <cstdint>
#include <gtest/gtest.h>

namespace {

Program make_program(std::initializer_list<Program::Instruction> instructions) {
  return Program{instructions};
}

} // namespace

TEST(brainfsck, initializer_list_constructor_preserves_instruction_order) {
  const Program program{
    Program::Instruction::INCREMENT,
    Program::Instruction::DECREMENT,
    Program::Instruction::SHIFT_PTR_LEFT,
    Program::Instruction::SHIFT_PTR_RIGHT,
    Program::Instruction::BEGIN_LOOP,
    Program::Instruction::END_LOOP,
  };

  EXPECT_EQ(program.size(), 6u);
  EXPECT_EQ(program.peek(0), Program::Instruction::INCREMENT);
  EXPECT_EQ(program.peek(1), Program::Instruction::DECREMENT);
  EXPECT_EQ(program.peek(2), Program::Instruction::SHIFT_PTR_LEFT);
  EXPECT_EQ(program.peek(3), Program::Instruction::SHIFT_PTR_RIGHT);
  EXPECT_EQ(program.peek(4), Program::Instruction::BEGIN_LOOP);
  EXPECT_EQ(program.peek(5), Program::Instruction::END_LOOP);
}

TEST(brainfsck, run_executes_linear_program_from_initializer_list) {
  const Program program = make_program({
    Program::Instruction::INCREMENT,
    Program::Instruction::INCREMENT,
    Program::Instruction::SHIFT_PTR_RIGHT,
    Program::Instruction::DECREMENT,
    Program::Instruction::SHIFT_PTR_LEFT,
  });

  Machine machine{0u};

  Brainfsck::run(program, machine);

  EXPECT_EQ(machine.get_pos(), 0u);
  EXPECT_EQ(machine.peek(), static_cast<uint8_t>(2u));
}

TEST(brainfsck, run_supports_pointer_wraparound) {
  const Program program = make_program({
    Program::Instruction::SHIFT_PTR_LEFT,
    Program::Instruction::SHIFT_PTR_RIGHT,
    Program::Instruction::SHIFT_PTR_RIGHT,
  });

  Machine machine{0u};

  Brainfsck::run(program, machine);

  EXPECT_EQ(machine.get_pos(), 1u);
  EXPECT_EQ(machine.peek(), static_cast<uint8_t>(0u));
}

TEST(brainfsck, run_supports_cell_value_wraparound) {
  const Program program = make_program({
    Program::Instruction::DECREMENT,
    Program::Instruction::INCREMENT,
  });

  Machine machine{0u};

  Brainfsck::run(program, machine);

  EXPECT_EQ(machine.get_pos(), 0u);
  EXPECT_EQ(machine.peek(), static_cast<uint8_t>(0u));
}

TEST(brainfsck, can_express_loop_based_computation_for_turing_complete_core) {
  const Program program = make_program({
    Program::Instruction::INCREMENT,
    Program::Instruction::INCREMENT,
    Program::Instruction::INCREMENT,
    Program::Instruction::INCREMENT,
    Program::Instruction::INCREMENT,
    Program::Instruction::BEGIN_LOOP,
    Program::Instruction::SHIFT_PTR_RIGHT,
    Program::Instruction::INCREMENT,
    Program::Instruction::SHIFT_PTR_LEFT,
    Program::Instruction::DECREMENT,
    Program::Instruction::END_LOOP,
    Program::Instruction::SHIFT_PTR_RIGHT,
  });

  Machine machine{0u};

  Brainfsck::run(program, machine);

  EXPECT_EQ(machine.get_pos(), 1u);
  EXPECT_EQ(machine.peek(), static_cast<uint8_t>(5u));
}

TEST(brainfsck, nested_loops_are_preserved_by_initializer_list_constructor) {
  const Program program = make_program({
    Program::Instruction::BEGIN_LOOP,
    Program::Instruction::BEGIN_LOOP,
    Program::Instruction::INCREMENT,
    Program::Instruction::END_LOOP,
    Program::Instruction::END_LOOP,
    Program::Instruction::SHIFT_PTR_RIGHT,
  });

  EXPECT_EQ(program.size(), 6u);
  EXPECT_EQ(program.peek(0), Program::Instruction::BEGIN_LOOP);
  EXPECT_EQ(program.peek(1), Program::Instruction::BEGIN_LOOP);
  EXPECT_EQ(program.peek(2), Program::Instruction::INCREMENT);
  EXPECT_EQ(program.peek(3), Program::Instruction::END_LOOP);
  EXPECT_EQ(program.peek(4), Program::Instruction::END_LOOP);
  EXPECT_EQ(program.peek(5), Program::Instruction::SHIFT_PTR_RIGHT);
}

int main(void) {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
