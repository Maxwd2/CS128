#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::string VowelsToPhonetics(std::string input) {
  std::string lower_case = input;
  std::string phon;
  std::vector<std::string> to_compare = {"iw","ew",   "ai", "ae",  "ao", "au", "ei",  "eu",   "iu", "oi", "ou",  "ui",   "a",  "e",  "i",  "o",  "u", "p", "k","h","l","m","n","w"};
  std::vector<std::string> to_insert = {"ee-v","eh-v","eye-","eye-","ow-","ow-","ay-","eh-oo-","ew-","oy-","ow-","ooey-", "ah-","eh-","ee-","oh-","oo-","p","k","h","l","m","n","w"};
  for (unsigned long i = 0; i < input.size(); i++) {
    lower_case[i] = tolower(input[i]);
  }
  for (unsigned int i = 0; i < lower_case.size(); i++) {
    for (unsigned int j = 0; j < to_compare.size(); j++) {
      std::string temp = to_compare[j];
      std::string temp_two = lower_case.substr(i, 2);
      if (lower_case.substr(i, 2) == to_compare[j]) {
        phon.append(to_insert[j]);
        i++;
        j = to_compare.size() + 1;
      } else if (lower_case.substr(i, 1) == to_compare[j]) {
        phon.append(to_insert[j]);
        j = to_compare.size() + 1;
      } else if (lower_case[i] == '\'') {
        phon.pop_back();
        phon.push_back('\'');
      } else if (lower_case[i] == ' ') {
        phon.pop_back();
        phon.push_back(' ');
      }
    }
  }
  phon.pop_back();
  if (lower_case.find_first_not_of("aeioupkhlmnw' ") != std::string::npos) {
    return input + " contains a character not a part of the Hawaiian language.";
  }
  return phon;
}