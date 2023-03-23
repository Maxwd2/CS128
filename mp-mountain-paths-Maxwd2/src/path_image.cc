#include "path_image.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  path_image_ = image.GetImage();
  width_ = dataset.Width();
  height_ = dataset.Height();
  bool first = true;
  unsigned int change = 0;
  for (size_t i = 0; i < height_; i++) {
    paths_.push_back(PathMaker(dataset, i));
    if (first) {
      change = paths_[i].EleChange();
      best_path_row_ = paths_[i].StartingRow();
      first = false;
    } else if (paths_[i].EleChange() < change) {
      best_path_row_ = paths_[i].StartingRow();
      change = paths_[i].EleChange();
    }
  }
  PathImageMaker();
}

Path PathImage::PathMaker(const ElevationDataset& dataset, size_t idx) const {
  Path p = Path(dataset.Width(), idx);
  for (size_t j = 0; j < width_ - 1; j++) {
    if (idx == 0) {
      PathMakerAtTop(dataset, p, idx, j);
    } else if (idx > 0 && idx < dataset.Height() - 1) {
      PathMakerAtMiddle(dataset, p, idx, j);
    } else if (idx == dataset.Height() - 1) {
      PathMakerAtBottom(dataset, p, idx, j);
    }
  }
  p.SetLoc(width_ - 1, idx);
  return p;
}

void PathImage::PathMakerAtTop(const ElevationDataset& dataset,
                               Path& p,
                               size_t& idx_i,
                               size_t& idx_j) const {
  p.SetLoc(idx_j, idx_i);
  int forward = std::abs(dataset.DatumAt(idx_i, idx_j) -
                         dataset.DatumAt(idx_i, idx_j + 1));
  int downward = std::abs(dataset.DatumAt(idx_i, idx_j) -
                          dataset.DatumAt(idx_i + 1, idx_j + 1));
  if (forward < downward || forward == downward) {
    p.IncEleChange(forward);
  } else if (downward < forward) {
    p.IncEleChange(downward);
    idx_i++;
  }
}
// 12 16
// 10 16
// 12 15
void PathImage::PathMakerAtMiddle(const ElevationDataset& dataset,
                                  Path& p,
                                  size_t& idx_i,
                                  size_t& idx_j) const {
  p.SetLoc(idx_j, idx_i);
  int upward = std::abs(dataset.DatumAt(idx_i, idx_j) -
                        dataset.DatumAt(idx_i - 1, idx_j + 1));
  int forward = std::abs(dataset.DatumAt(idx_i, idx_j) -
                         dataset.DatumAt(idx_i, idx_j + 1));
  int downward = std::abs(dataset.DatumAt(idx_i, idx_j) -
                          dataset.DatumAt(idx_i + 1, idx_j + 1));
  if (upward < forward && upward < downward) {
    p.IncEleChange(upward);
    idx_i--;
  } else if ((forward < upward && forward < downward) ||
             (forward == upward && forward == downward) ||
             (forward == upward && forward < downward) ||
             (forward == downward && forward < upward)) {
    p.IncEleChange(forward);
  } else if ((downward < upward && downward < forward) ||
             (downward == upward && downward != forward)) {
    p.IncEleChange(downward);
    idx_i++;
  }
}

void PathImage::PathMakerAtBottom(const ElevationDataset& dataset,
                                  Path& p,
                                  size_t& idx_i,
                                  size_t& idx_j) const {
  p.SetLoc(idx_j, idx_i);
  int upward = std::abs(dataset.DatumAt(idx_i, idx_j) -
                        dataset.DatumAt(idx_i - 1, idx_j + 1));
  int forward = std::abs(dataset.DatumAt(idx_i, idx_j) -
                         dataset.DatumAt(idx_i, idx_j + 1));
  if (upward < forward) {
    p.IncEleChange(upward);
    idx_i--;
  } else if (forward < upward || forward == upward) {
    p.IncEleChange(forward);
  }
}

void PathImage::PathImageMaker() {
  Color red = Color(kRedR, kRedG, kRedB);
  Color green = Color(kGreenR, kGreenG, kGreenB);
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      path_image_.at(paths_.at(i).GetPath().at(j)).at(j) = red;
    }
  }
  for (size_t k = 0; k < width_; k++) {
    path_image_.at(paths_.at(best_path_row_).GetPath().at(k)).at(k) = green;
  }
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << '\n' << width_ << " " << height_ << '\n' << "255" << '\n';
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      ofs << path_image_[i][j].Red() << " " << path_image_[i][j].Green() << " "
          << path_image_[i][j].Blue() << " ";
    }
    ofs << '\n';
  }
  std::cout << name;
}