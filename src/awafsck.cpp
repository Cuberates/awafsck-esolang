#include <iostream> 
#include <cstring>
#include <unordered_map>
#include <string>
#include <cassert>
#include <gtest/gtest.h> 
#include "../lib/program.hpp"
#include "../lib/machine.hpp"
#include "../lib/brainfsck.hpp"

namespace Parser { 
  std::unordered_map<std::string, Program::Instruction> TABLE = { 
    {"awa~", Program::Instruction::INCREMENT},
    {"awa!", Program::Instruction::DECREMENT},
    {"owo~", Program::Instruction::SHIFT_PTR_RIGHT}, 
    {"owo!", Program::Instruction::SHIFT_PTR_LEFT},
    {"start_train!", Program::Instruction::BEGIN_LOOP}, 
    {"end_train!", Program::Instruction::END_LOOP},
    {"explode!", Program::Instruction::PRINT},
  };

  std::runtime_error EXTENSION_EXCEPT("Invalid file extension!");
  std::runtime_error ARGUMENT_EXCEPT("Invalid arguments!");
  std::runtime_error INVALID_SYNTAX("Invalid syntax!");

  void parse_from_file(Program& program, const char* src_file_path); 
  void parse_from_string(Program& program, const std::string& s);
  void verify_file_path(const char* src_file_path);
  void process(Program& program, const std::string& token);
}

void Parser::process(Program& program, const std::string& token) { 
  if (TABLE.find(token) == TABLE.end()) 
    throw Parser::INVALID_SYNTAX;
  program.push(TABLE[token]);
}

void Parser::parse_from_file(Program& program, const char* src_file_path) { 
  // std::cout << src_file_path << "\n";
  verify_file_path(src_file_path);
  freopen(src_file_path, "r", stdin); 
  std::string token; 
  while (std::cin >> token) { 
    process(program, token);
  }
}

void Parser::verify_file_path(const char* src_file_path) { 
  std::exception ex = std::runtime_error("Incorrect extension!");
  const auto sz = strlen(src_file_path);
  std::string ext = ""; 
  bool found_ext = false; 
  for(auto i {0}; i < sz; i++) { 
    if (src_file_path[i] == '.') { 
      for(auto j = i+1; j < sz; j++) { 
        ext += src_file_path[j];  
      }
      // std::cout << ext << "\n";
      if (ext != "awa") throw Parser::EXTENSION_EXCEPT;
      found_ext = true;
    }
  }
  if (!found_ext)
    throw Parser::EXTENSION_EXCEPT; 
}

int main(int argc, char* argv[]) {
  if (argc != 2) throw Parser::ARGUMENT_EXCEPT; 

  Program program; 
  Machine machine;
  
  Parser::parse_from_file(program, argv[1]);
  Brainfsck::run(program, machine);
}
