#ifndef PATH_H
#define PATH_H

#include <cassert>
#include <cmath>
#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class Path {
public:
  // Maybe done
  Path(size_t length, size_t starting_row);

  // All 3 done
  size_t Length() const { return length_; };
  size_t StartingRow() const { return starting_row_; };
  unsigned int EleChange() const { return ele_change_; };
  const std::vector<size_t>& GetPath() const { return path_; };

  // Done
  void IncEleChange(unsigned int value);

  // Maybe done
  void SetLoc(size_t col, size_t row);

private:
  size_t length_;
  size_t starting_row_;
  std::vector<size_t> path_;
  unsigned int ele_change_ = 0;
};

#endif