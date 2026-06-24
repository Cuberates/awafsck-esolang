#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <vector>  
#include <string> 
#include <filesystem>

#include "program.hpp"

namespace Parser {
  void verify(const std::filesystem::path& file_path);
  void parse(Program &program_, std::ifstream& source_file);
}

void Parser::verify(const std::filesystem::path& file_path) { 
  if (file_path.extension() != ".awa") 
    throw std::runtime_error("Cannot recognize .awa file extension!"); 
} 

void Parser::parse(Program &program_, std::ifstream& source_file) {
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
#endif PARSER_H
  