#include "elevation_dataset.hpp"

// Not Done, need to shorten
ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height) {
  std::ifstream ifs(filename);
  std::vector<int> vect = FileReadHelper(filename);
  std::vector<int> temp;
  int min_ele = 0;
  int max_ele = 0;
  bool first = true;
  for (size_t i = 0; i < height; i++) {
    temp.clear();
    for (size_t j = 0; j < width; j++) {
      temp.push_back(vect[j + (i * width)]);
      if (first) {
        min_ele = vect[j + (i * width)];
        max_ele = vect[j + (i * width)];
        first = false;
      }
      if (min_ele > vect[j + (i * width)]) {
        min_ele = vect[j + (i * width)];
      }
      if (max_ele < vect[j + (i * width)]) {
        max_ele = vect[j + (i * width)];
      }
    }
    data_.push_back(temp);
  }
  if (data_points_ != height * width) {
    throw std::runtime_error("Wrong number of data points/invalid file read");
  }
  max_ele_ = max_ele;
  min_ele_ = min_ele;
  width_ = width;
  height_ = height;
}

std::vector<int> ElevationDataset::FileReadHelper(const std::string& filename) {
  std::ifstream ifs(filename);
  std::vector<int> vect;
  int value = 0;
  while (ifs.good()) {
    ifs >> value;
    if (ifs.fail()) {
      ifs.clear();
      ifs.ignore(1, '\n');
    } else {
      vect.push_back(value);
      data_points_++;
    }
    std::vector<int> vect;
  }
  return vect;
}
