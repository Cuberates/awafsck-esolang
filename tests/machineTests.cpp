#include "../lib/machine.hpp"
#include <gtest/gtest.h> 
#include <limits>

TEST(machine_init, init_default) { 
  Machine machine; 
  EXPECT_TRUE(machine.get_pos() == 0u);
}

TEST(machine_command, increment_ptr_val) { 
  Machine machine;
  machine.increment(); 
  EXPECT_TRUE(machine.peek() == 1);
  machine.increment(); 
  EXPECT_TRUE(machine.peek() == 2);
}

TEST(machine_command, increment_ptr_val_wrap) { 
  Machine machine; 
  for (size_t counter{0}; counter < std::numeric_limits<uint8_t>::max(); counter++) {
    machine.increment();
  }
  EXPECT_TRUE(machine.peek() == std::numeric_limits<uint8_t>::max());
  machine.increment(); 
  EXPECT_TRUE(machine.peek() == std::numeric_limits<uint8_t>::min());
}

TEST(machine_command, decrement_ptr_val) { 
  Machine machine;
  machine.increment(); 
  EXPECT_TRUE(machine.peek() == 1);
  machine.decrement(); 
  EXPECT_TRUE(machine.peek() == 0);
}

TEST(machine_command, decrement_ptr_val_wrap) { 
  Machine machine; 
  EXPECT_TRUE(machine.peek() == std::numeric_limits<uint8_t>::min());
  machine.decrement();
  EXPECT_TRUE(machine.peek() == std::numeric_limits<uint8_t>::max());
}

TEST(machine_comamnd, inst_ptr_shift_right) { 
  Machine machine; 
  EXPECT_TRUE(machine.peek() == 0); 
  machine.increment(); 
  machine.shift_right(); 
  EXPECT_TRUE(machine.get_pos() == 1);
  EXPECT_TRUE(machine.peek() == 0);
}

TEST(machine_comamnd, inst_ptr_shift_left) { 
  Machine machine; 
  EXPECT_TRUE(machine.peek() == 0); 
  machine.increment(); 
  machine.shift_right(); 
  EXPECT_TRUE(machine.get_pos() == 1);
  EXPECT_TRUE(machine.peek() == 0);
  machine.shift_left(); 
  EXPECT_TRUE(machine.get_pos() == 0);
  EXPECT_TRUE(machine.peek() == 1);
}

TEST(machine_command, inst_ptr_shift_right_wrap) { 
  Machine machine; 
  for (size_t counter{0}; counter < (REGISTER_CAPACITY_MAX - 1); counter++) {
    machine.shift_right();
  }
  EXPECT_TRUE(machine.get_pos() == REGISTER_CAPACITY_MAX - 1);
  machine.shift_right(); 
  EXPECT_TRUE(machine.get_pos() == 0);
}

TEST(machine_command, inst_ptr_shift_left_wrap) { 
  Machine machine; 
  machine.shift_left();
  EXPECT_TRUE(machine.get_pos() == REGISTER_CAPACITY_MAX-1);
}

int main() { 
  ::testing::InitGoogleTest(); 
  return RUN_ALL_TESTS();
}