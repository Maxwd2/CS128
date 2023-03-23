#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

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
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  // Done, maybe
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);

  // All 5 Done
  size_t Width() const { return width_; };
  size_t Height() const { return height_; };
  unsigned int MaxColorValue() const { return kMaxColorValue; };
  const std::vector<Path>& Paths() const { return paths_; };
  const std::vector<std::vector<Color>>& GetPathImage() const {
    return path_image_;
  };

  // Done
  size_t BestPathRow() const { return best_path_row_; }

  // Done, maybe
  void ToPpm(const std::string& name) const;

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  static const int kRedR = 252;
  static const int kRedG = 25;
  static const int kRedB = 63;
  static const int kGreenR = 31;
  static const int kGreenG = 253;
  static const int kGreenB = 13;
  // implemented
  size_t best_path_row_{};

  // Done, maybe
  Path PathMaker(const ElevationDataset& dataset, size_t idx) const;
  void PathMakerAtTop(const ElevationDataset& dataset,
                      Path& p,
                      size_t& idx_i,
                      size_t& idx_j) const;
  void PathMakerAtMiddle(const ElevationDataset& dataset,
                         Path& p,
                         size_t& idx_i,
                         size_t& idx_j) const;
  void PathMakerAtBottom(const ElevationDataset& dataset,
                         Path& p,
                         size_t& idx_i,
                         size_t& idx_j) const;

  // almost done, green path gets overwritten
  void PathImageMaker();
};

#endif