#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "functions.hpp"

std::string ToLowerCase(std::string input) {
  std::string lower_case = input;
  for (unsigned long i = 0; i < input.size(); i++) {
      lower_case[i] = tolower(input[i]);
    }
  return lower_case;
}
std::string SinglePhonetics(std::string lower_case) {
  for (unsigned int i = 0; i < lower_case.size(); i++) {
    
  }
}
std::string WordsToPhonetics(std::string lower_case) {
  std::string phon;
  std::vector<char> to_compare = {'a', 'e', 'i', 'o', 'u'};
  std::vector<std::string> to_insert = {"ah-", "eh-", "ee-", "oh-", "oo-"};
  
  for (unsigned int i = 0; i < lower_case.size(); i++) {
    for (unsigned int j = 0; j < to_compare.size(); j++) {
      if (lower_case[i] == to_compare[j]) {
        phon.append(to_insert[j]);
        i++;
      }
    }
    if (lower_case[i] == 'w' && i == 0) {
      phon.push_back('w');
    } else if (lower_case[i] == 'w' &&
               (lower_case[i - 1] == 'i' || lower_case[i - 1] == 'e')) {
      phon.push_back('v');
    } else if ((lower_case[i] == 'a' && lower_case[i + 1] == 'i') ||
               (lower_case[i] == 'a' && lower_case[i + 1] == 'e')) {
      phon.append("eye-");
      i++;
    } else if ((lower_case[i] == 'a' && lower_case[i + 1] == 'o') ||
               (lower_case[i] == 'a' && lower_case[i + 1] == 'u') ||
               (lower_case[i] == 'o' && lower_case[i + 1] == 'u')) {
      phon.append("ow-");
      i++;
    } else if (lower_case[i] == 'e' && lower_case[i + 1] == 'i') {
      phon.append("ay-");
      i++;
    } else if (lower_case[i] == 'e' && lower_case[i + 1] == 'u') {
      phon.append("eh-oo-");
      i++;
    } else if (lower_case[i] == 'i' && lower_case[i + 1] == 'u') {
      phon.append("ew-");
      i++;
    } else if (lower_case[i] == 'o' && lower_case[i + 1] == 'i') {
      phon.append("oy-");
      i++;
    } else if (lower_case[i] == 'u' && lower_case[i + 1] == 'i') {
      phon.append("ooey-");
      i++;
    } else if (lower_case[i] == 'a') {
      phon.append("ah-");
    } else if (lower_case[i] == 'e') {
      phon.append("eh-");
    } else if (lower_case[i] == 'i') {
      phon.append("ee-");
    } else if (lower_case[i] == 'o') {
      phon.append("oh-");
    } else if (lower_case[i] == 'u') {
      phon.append("oo-");
    } else if (lower_case[i] == '\'') {
      phon.pop_back();
      phon.push_back('\'');
    } else if (lower_case[i] == ' ') {
      phon.pop_back();
      phon.push_back(' ');
    } else {
      phon.push_back(lower_case[i]);
    }
  }
  std::size_t found = lower_case.find_first_not_of("aeioupkhlmnw' ");
  if (found != std::string::npos) {
    return lower_case + " contains a character not a part of the Hawaiian language.";
  }
  return phon;
}