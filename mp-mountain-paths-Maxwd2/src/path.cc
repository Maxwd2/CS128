#include "path.hpp"

Path::Path(size_t length, size_t starting_row) {
  length_ = length;
  starting_row_ = starting_row;
  path_.resize(length_);
}

void Path::IncEleChange(unsigned int value) {
  if (value < 0) {
    throw std::invalid_argument("increment not positive");
  };
  ele_change_ += value;
}
// path_.at(j) = i;
void Path::SetLoc(size_t col, size_t row) { path_.at(col) = row; }