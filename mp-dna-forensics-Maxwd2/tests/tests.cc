#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <catch/catch.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "functions.hpp"

TEST_CASE("Testing CSVToDoubleVector", "[case-1]") {
  // REQUIRE(CSVToDoubleVector("data.dat"));
}
TEST_CASE("Testing DNAToConsecutiveSTR", "[case-2]") {
  std::vector<std::string> names = {"AGATG", "AATG", "TAT"};
  std::string dna_input = "TATTATTATTATAACCCTGC";
  // REQUIRE(DNAToConsecutiveSTR(dna_input, names) == )
}