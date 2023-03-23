#include <iostream>
#include <string>

#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }

  std::string word = argv[1];

  //std::string phonetics = ToLowerCase(word);
  std::cout << VowelsToPhonetics(word) << std::endl;
}

// Only allowed to use these headers: <cassert> <cctype> <iostream> <sstream>
//  <string> <utility> <vector> "functions.hpp"