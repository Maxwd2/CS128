#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

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

#include "color.hpp"
#include "elevation_dataset.hpp"

// empyt functions/variables done
class GrayscaleImage {
public:
  // Done
  GrayscaleImage(const ElevationDataset& dataset);
  // Done
  GrayscaleImage(const std::string& filename, size_t width, size_t height);

  // Both Done
  size_t Width() const { return width_; };
  size_t Height() const { return height_; };

  // Done
  unsigned int MaxColorValue() const { return kMaxColorValue; };
  const std::vector<std::vector<Color>>& GetImage() const { return image_; };

  // Done
  const Color& ColorAt(int row, int col) const;

  // Done, maybe, not sure if additional whitespace at the end of each line
  // matters
  // apparently It doesn't
  void ToPpm(const std::string& name) const;

private:
  size_t width_{};
  size_t height_{};
  std::vector<std::vector<Color>> image_;
  static const int kMaxColorValue = 255;
  static const int kTen = 10;
};

#endif