# Program Interface

## Overview
`Program` is a container for `Program::Instruction` values. It stores instructions in insertion order inside a `std::vector` and exposes a small interface for appending instructions and inspecting either the most recently pushed instruction or an instruction at a specific index.

The instruction types currently supported by the interface are:

- `Program::Instruction::INCREMENT`
- `Program::Instruction::DECREMENT`
- `Program::Instruction::SHIFT_PTR_LEFT`
- `Program::Instruction::SHIFT_PTR_RIGHT`
- `Program::Instruction::INSTRUCTION_NULL`

`INSTRUCTION_NULL` is reserved as an invalid value for `push()` and is used as a guard rather than a normal instruction.

## Attributes

### Private Attributes

#### `_inst_capacity`

Type: `size_t`

Tracks the current allocated capacity of the internal instruction storage. The constructor initializes it to `1024`. When the number of stored instructions reaches this capacity, the value is doubled and the internal vector is resized.

Usage notes:

- This field is implementation detail and is not accessible from outside the class.
- It represents allocated storage, not the number of active instructions.

#### `_inst_end`

Type: `size_t`

Tracks how many valid instructions have been pushed into the program. It is also the index where the next instruction will be inserted.

Usage notes:

- `size()` returns `_inst_end`.
- Valid indexed access through `peek(size_t)` is in the range `0` to `_inst_end - 1`.
- When `_inst_end` is `0`, the program is empty.

#### `_inst_list`

Type: `std::vector<Instruction>`

Stores the actual instructions. The vector is created with `_inst_capacity` slots during construction and grows when more capacity is needed.

Usage notes:

- Instructions are inserted in order from index `0` upward.
- `peek()` reads the last pushed instruction from `_inst_list[_inst_end - 1]`.
- `peek(size_t)` reads a specific instruction from `_inst_list[_pos]`.

## Methods

### `push(Instruction _inst)`

Appends one instruction to the end of the program.

Behavior:

- Rejects `Program::Instruction::INSTRUCTION_NULL` by throwing `std::runtime_error`.
- Stores the instruction at the current end position.
- Increments `_inst_end` after insertion.
- Doubles capacity and resizes the internal vector when the storage limit is reached.

Example:

```cpp
Program program;

program.push(Program::Instruction::INCREMENT);
program.push(Program::Instruction::SHIFT_PTR_RIGHT);
```

When to use it:

- Use `push()` when building a program instruction by instruction.
- Use it repeatedly when parsing source input into executable instructions.

Error case:

```cpp
Program program;
program.push(Program::Instruction::INSTRUCTION_NULL); // throws std::runtime_error
```

### `peek() const`

Returns a reference to the most recently pushed instruction.

Behavior:

- Reads the last valid instruction currently stored in the container.
- Does not remove the instruction.
- Throws `std::runtime_error` if the program is empty.

Example:

```cpp
Program program;
program.push(Program::Instruction::DECREMENT);
program.push(Program::Instruction::SHIFT_PTR_LEFT);

const Program::Instruction& last = program.peek();
// last == Program::Instruction::SHIFT_PTR_LEFT
```

When to use it:

- Use `peek()` when only the newest instruction matters.
- Use it to inspect the tail of the instruction list after a sequence of pushes.

Error case:

```cpp
Program program;
program.peek(); // throws std::runtime_error because the program is empty
```

### `peek(size_t _pos) const`

Returns a reference to the instruction stored at index `_pos`.

Behavior:

- Reads a specific instruction by zero-based position.
- Does not modify the container.
- Throws `std::runtime_error` if `_pos` is greater than or equal to `_inst_end`.

Example:

```cpp
Program program;
program.push(Program::Instruction::INCREMENT);
program.push(Program::Instruction::DECREMENT);
program.push(Program::Instruction::SHIFT_PTR_RIGHT);

const Program::Instruction& first = program.peek(0);
const Program::Instruction& second = program.peek(1);
const Program::Instruction& third = program.peek(2);
```

Expected values:

- `first` is `Program::Instruction::INCREMENT`
- `second` is `Program::Instruction::DECREMENT`
- `third` is `Program::Instruction::SHIFT_PTR_RIGHT`

When to use it:

- Use `peek(size_t)` when you need indexed access to an earlier instruction.
- Use it for tests, inspection, or parser validation where insertion order matters.

Error case:

```cpp
Program program;
program.push(Program::Instruction::INCREMENT);

program.peek(1); // throws std::runtime_error because index 1 is out of range
```

## Summary

`Program` currently exposes a minimal container interface:

- `push()` adds validated instructions.
- `peek()` reads the last instruction.
- `peek(size_t)` reads an instruction at a specific zero-based index.

Internally, `_inst_end` tracks the number of valid instructions, `_inst_capacity` tracks allocated storage, and `_inst_list` owns the instruction data.