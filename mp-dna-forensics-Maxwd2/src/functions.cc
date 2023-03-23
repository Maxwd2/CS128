#include "functions.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utilities.hpp"

// Each vector is a row, with each string being an element in the collumn
// The first row is the info, the first collumn is the names
std::vector<std::vector<std::string>> CSVToDoubleVector(
    std::string csv_file_name) {
  std::ifstream ifs{csv_file_name};
  std::vector<std::vector<std::string>> output;
  std::vector<std::string> lines;
  for (std::string line; std::getline(ifs, line); line = "") {
    lines.push_back(line);
  }
  for (unsigned int i = 0; i < lines.size(); i++) {
    std::vector<std::string> temp;
    temp = utilities::GetSubstrs(lines[i], ',');
    if (!temp.empty()) {
      output.push_back(temp);
    }
    temp.clear();
  }
  return output;
}

// Isolates the names of the STRs for easier use
std::vector<std::string> GetSTRNames(
    std::vector<std::vector<std::string>> csv_double_vector) {
  std::vector<std::string> vect;
  for (unsigned int i = 1; i < csv_double_vector.at(0).size(); i++) {
    vect.push_back(csv_double_vector.at(0).at(i));
  }
  return vect;
}

// make a map or 2D vector where each key/vector is a STR and number pairing
//:map/vect = {"AATG", 5}; the number represents most consecutive occurences
std::map<std::string, int> DNAToConsecutiveSTR(
    std::string dna_input, std::vector<std::string> str_names) {
  // std::cout << "\nInside DNAToConsecutiveSTR" << std::endl;
  std::map<std::string, int> map;
  for (unsigned int i = 0; i < str_names.size(); i++) {
    int curr = 0;
    int largest = 0;
    bool dumb = true;
    for (unsigned int j = 0; j < dna_input.size(); j++) {
      if (str_names[i] == dna_input.substr(j, str_names[i].size())) {
        curr++;
        j += str_names[i].size() - 1;
        // std::cout << "\n" << curr << std::endl;
      } else if (dumb) {
        if (largest < curr) {
          largest = curr;
        }
        curr = 0;
      }
      if (largest < curr) {
        largest = curr;
      }
    }
    map[str_names[i]] = largest;
  }
  return map;
}

std::string CompareDNA(std::map<std::string, int> map,
                       std::vector<std::vector<std::string>> data,
                       std::vector<std::string> str_names) {
  // std::cout << "\nInside CompareDNA:" << std::endl;
  std::vector<std::string> matches;
  for (unsigned int i = 1; i < data.size(); i++) {
    std::string curr_name;
    unsigned long count = 0;
    for (unsigned int j = 1; j < data.at(i).size(); j++) {
      curr_name = data.at(i).at(0);
      // std::cout << "\n";
      int num = std::stoi(data.at(i).at(j));
      if (num == map[str_names[j - 1]]) {
        count++;
      }
      if (count == str_names.size()) {
        matches.push_back(data.at(i).at(0));
      }
    }
  }
  if (matches.empty()) {
    return "No Match";
  }
  for (unsigned int i = 0; i < matches.size(); i++) {
    for (unsigned int j = 0; j < matches.size(); j++) {
      if (matches[i] != matches[j]) {
        return "No Match";
      }
    }
  }
  return matches[0];
}