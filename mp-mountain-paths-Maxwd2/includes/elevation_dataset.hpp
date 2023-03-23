#ifndef ELEVATION_DATASET_H
#define ELEVATION_DATASET_H

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

// Empty functions/variables done
class ElevationDataset {
public:
  // Done, maybe
  ElevationDataset(const std::string& filename, size_t width, size_t height);

  // Both Done
  size_t Width() const { return width_; };
  size_t Height() const { return height_; };

  // All 3 Done
  int MaxEle() const { return max_ele_; };
  int MinEle() const { return min_ele_; };
  const std::vector<std::vector<int>>& GetData() const { return data_; };

  // Done
  int DatumAt(size_t row, size_t col) const { return data_.at(row).at(col); };

private:
  size_t width_{};
  size_t height_{};
  std::vector<std::vector<int>> data_;
  int max_ele_{};
  int min_ele_{};
  size_t data_points_{};
  // Done, maybe
  std::vector<int> FileReadHelper(const std::string& filename);
};

#endif