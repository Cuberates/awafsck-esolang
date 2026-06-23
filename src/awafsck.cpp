#include <iostream>
#include <fstream>
#include <vector>  
#include <string> 
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
  /**
   * @todo Implement complete tokenizer HERE
   * @author Xuan Viet Duc Nguyen
   */
}

void Brainfsck::run(const Program &program_, Machine &machine) { 
   /**
   * @todo Emulate Awa Brainfsck instructions HERE
   * @author Xuan Viet Duc Nguyen
   */ 
}

int main(int argc, char** argv) { 
  if (argc != 2) { 
    std::cerr << "Too many arguments!" << std::endl;
    return 0; 
  }

  std::filesystem::path file_path = argv[1];
  try { Brainfsck::verify(file_path); } 
  
  catch (const std::runtime_error& err) { 
    std::cerr << err.what() << std::endl;
    return 0;
  }

  std::ifstream source_file(argv[1]);
  
  if (!source_file.is_open()) {
    std::cerr << "Cannot read source file!" << std::endl;
    return 0;
  }

  Program brainfsck_program;
  Machine brainfsck_machine;

  Brainfsck::parse(brainfsck_program, source_file);
  // Brainfsck::run(brainfsck_program, brainfsck_machine);
}
