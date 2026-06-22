#include <iostream>
#include <fstream>
#include <vector>  
#include <string>

/**
 * @brief File parser for organizing Awa syntaxes
 * @todo - Transcribe all lines into tokens to be stored in some sort of stack? 
 *       - Perform string parsing using std::string, but still trying to find a much quicker way
 */

int main(int argc, char** argv) { 
  if (argc != 2) {
    throw std::runtime_error("Too many arguments!");  
    return 1;
  }
  std::ifstream source_file(argv[1]);

  if (!source_file.is_open()) { 
    throw std::runtime_error("Cannot read source_file");
    return 1; 
  }

  std::vector<std::string> lines; 

  std::string line;
  while (std::getline(source_file, line)) {
    lines.push_back(line);

    if (!source_file.eof()) {
      lines.push_back("\n");
    }
  }

  for(size_t l{0}; l < lines.size(); l++) {
    std::cout << lines[l] << "\n";
  }
}
