#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utilities.hpp"
// Takes the CSV file and converts it to 2D vect, the 0th vect is the names of
// the STRs
// DONE
std::vector<std::vector<std::string>> CSVToDoubleVector(
    std::string csv_file_name);

// simple function that just makes a vector of the STR names
// TO NOTE: removes "Names" at element 0
// DONE
std::vector<std::string> GetSTRNames(
    std::vector<std::vector<std::string>> csv_double_vector);

// Takes the input DNA strand and inputs the STRs as keys and their largest
// consecutive amounts as values
// DONE
std::map<std::string, int> DNAToConsecutiveSTR(
    std::string dna_input, std::vector<std::string> str_names);

// This is where the comparing happens
std::string CompareDNA(std::map<std::string, int> map,
                       std::vector<std::vector<std::string>> data,
                       std::vector<std::string> str_names);

#endif