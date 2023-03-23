#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }

  std::string to_compare = argv[2];
  std::string csv_file_name = argv[1];
  std::vector<std::vector<std::string>> data;

  data = CSVToDoubleVector(csv_file_name);
  std::vector<std::string> names = GetSTRNames(data);
  std::map<std::string, int> consecutive =
      DNAToConsecutiveSTR(to_compare, names);
  /*
    std::cout << "Testing CSVToDoubleVector:" << std::endl;
    for (std::vector<std::string> vect : data) {
      for (std::string s : vect) {
        std::cout << s << " + ";
      }
      std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "Testing GetSTRNames:" << std::endl;
    for (std::string s : names) {
      std::cout << s << " ";
    }
    std::cout << "\n\n";

    std::cout << "Printing DNAToConsecutiveSTR:" << std::endl;
    for (auto m : consecutive) {
      std::cout << m.first << "," << m.second << std::endl;
    }
  */
  std::cout << CompareDNA(consecutive, data, names) << std::endl;
  return 0;
}
//
// bin/exec tests/data.dat "AGATGATATATTATTGAATGAATGTGTAT"
// bin/exec tests/data.dat
// "AGACGGGTTACCATGACTATTATTATTATTATTATTATTATACGTACGTACGTATGAGATGAGATGAGATGAGATGAGATGCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA"
// "AGATGTATAGATGTATTATTATAGATGAGATGTATTATTATTATTATAGATGAGATGCAAACAAAGACAG"
//"TATAATGTATTATTATTATTATTATTATTATTATTATTAT" 11

/*
  std::cout << "Testing CSVToDoubleVector:" << std::endl;
  for (std::vector<std::string> vect : data) {
    for (std::string s : vect) {
      std::cout << s << " + ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << "Testing GetSTRNames:" << std::endl;
  for (std::string s : names) {
    std::cout << s << " ";
  }
  std::cout << "\n\n";

  std::cout << "Testing DNAToConsecutiveSTR:" << std::endl;
  for (auto m : consecutive) {
    std::cout << m.first << "," << m.second << std::endl;
  }
  */