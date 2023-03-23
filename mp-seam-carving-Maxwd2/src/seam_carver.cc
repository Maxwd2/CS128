#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

int SeamCarver::GetEnergy(int row, int col) const {
  return GetHorizontalEnergy(row, col) + GetVerticalEnergy(row, col);
}

int SeamCarver::GetHorizontalEnergy(int static_row, int col) const {
  int red = 0;
  int blue = 0;
  int green = 0;
  if (col == 0) {
    red = image_.GetPixel(static_row, width_ - 1).GetRed() -
          image_.GetPixel(static_row, col + 1).GetRed();
    green = image_.GetPixel(static_row, width_ - 1).GetGreen() -
            image_.GetPixel(static_row, col + 1).GetGreen();
    blue = image_.GetPixel(static_row, width_ - 1).GetBlue() -
           image_.GetPixel(static_row, col + 1).GetBlue();
  } else if (col == width_ - 1) {
    red = image_.GetPixel(static_row, col - 1).GetRed() -
          image_.GetPixel(static_row, 0).GetRed();
    green = image_.GetPixel(static_row, col - 1).GetGreen() -
            image_.GetPixel(static_row, 0).GetGreen();
    blue = image_.GetPixel(static_row, col - 1).GetBlue() -
           image_.GetPixel(static_row, 0).GetBlue();
  } else {
    red = image_.GetPixel(static_row, col - 1).GetRed() -
          image_.GetPixel(static_row, col + 1).GetRed();
    green = image_.GetPixel(static_row, col - 1).GetGreen() -
            image_.GetPixel(static_row, col + 1).GetGreen();
    blue = image_.GetPixel(static_row, col - 1).GetBlue() -
           image_.GetPixel(static_row, col + 1).GetBlue();
  }
  return (red * red) + (green * green) + (blue * blue);
}

int SeamCarver::GetVerticalEnergy(int row, int static_col) const {
  int red = 0;
  int blue = 0;
  int green = 0;
  if (row == 0) {
    red = image_.GetPixel(height_ - 1, static_col).GetRed() -
          image_.GetPixel(row + 1, static_col).GetRed();
    green = image_.GetPixel(height_ - 1, static_col).GetGreen() -
            image_.GetPixel(row + 1, static_col).GetGreen();
    blue = image_.GetPixel(height_ - 1, static_col).GetBlue() -
           image_.GetPixel(row + 1, static_col).GetBlue();
  } else if (row == height_ - 1) {
    red = image_.GetPixel(row - 1, static_col).GetRed() -
          image_.GetPixel(0, static_col).GetRed();
    green = image_.GetPixel(row - 1, static_col).GetGreen() -
            image_.GetPixel(0, static_col).GetGreen();
    blue = image_.GetPixel(row - 1, static_col).GetBlue() -
           image_.GetPixel(0, static_col).GetBlue();
  } else {
    red = image_.GetPixel(row - 1, static_col).GetRed() -
          image_.GetPixel(row + 1, static_col).GetRed();
    green = image_.GetPixel(row - 1, static_col).GetGreen() -
            image_.GetPixel(row + 1, static_col).GetGreen();
    blue = image_.GetPixel(row - 1, static_col).GetBlue() -
           image_.GetPixel(row + 1, static_col).GetBlue();
  }
  return (red * red) + (green * green) + (blue * blue);
}

int* SeamCarver::GetHorizontalSeam() const {
  // Fills seams with original energy
  int** seams = new int*[height_];
  for (int row = 0; row < height_; row++) {
    seams[row] = new int[width_];
    for (int col = 0; col < width_; col++) {
      seams[row][col] = GetEnergy(row, col);
    }
  }
  // fills seams with least energy
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      if (row == 0) {
        seams[row][col] +=
            std::min(seams[row][col + 1], seams[row + 1][col + 1]);
      } else if (row == height_ - 1) {
        seams[row][col] +=
            std::min(seams[row][col + 1], seams[row - 1][col + 1]);
      } else {
        seams[row][col] += std::min(
            seams[row][col + 1],
            std::min(seams[row + 1][col + 1], seams[row - 1][col + 1]));
      }
    }
  }
  // calculates weakest seam
  int idx = 0;
  for (int row = 0; row < height_; row++) {
    if (seams[row][0] < seams[idx][0]) {
      idx = row;
    }
  }
  int* seam = HorizontalSeamFiller(seams, idx);
  // delete seams
  for (int row = 0; row < height_; row++) {
    delete[] seams[row];
  }
  delete[] seams;
  // return weakest seam
  return seam;
}

int* SeamCarver::HorizontalSeamFiller(int**& seams, int idx) const {
  int* seam = new int[width_];
  seam[0] = idx;

  for (int col = 0; col < width_ - 1; col++) {
    if (idx == 0) {
      if (seams[idx + 1][col + 1] < seams[idx][col + 1]) {
        idx++;
      }
    } else if (idx == height_ - 1) {
      if (seams[idx - 1][col + 1] < seams[idx][col + 1]) {
        idx--;
      }
    } else {
      if (seams[idx][col + 1] <= seams[idx - 1][col + 1] &&
          seams[idx][col + 1] <= seams[idx + 1][col + 1]) {
        // no nothing, idx doesn't change since middle
      } else if (seams[idx - 1][col + 1] < seams[idx][col + 1] &&
                 seams[idx - 1][col + 1] <= seams[idx + 1][col + 1]) {
        idx--;
      } else if (seams[idx + 1][col + 1] < seams[idx][col + 1] &&
                 seams[idx + 1][col + 1] < seams[idx - 1][col + 1]) {
        idx++;
      }
    }
    seam[col + 1] = idx;
  }

  return seam;
}

int* SeamCarver::GetVerticalSeam() const {
  // Fills seams with original energy
  int** seams = new int*[height_];
  for (int row = 0; row < height_; row++) {
    seams[row] = new int[width_];
    for (int col = 0; col < width_; col++) {
      seams[row][col] = GetEnergy(row, col);
    }
  }
  // fills seams with least energy
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) {
      if (col == 0) {
        seams[row][col] +=
            std::min(seams[row + 1][col], seams[row + 1][col + 1]);
      } else if (col == width_ - 1) {
        seams[row][col] +=
            std::min(seams[row + 1][col - 1], seams[row + 1][col]);
      } else {
        seams[row][col] +=
            std::min(seams[row + 1][col - 1],
                     std::min(seams[row + 1][col], seams[row + 1][col + 1]));
      }
    }
  }
  // calculates weakest seam
  int idx = 0;
  for (int col = 0; col < width_; col++) {
    if (seams[0][col] < seams[0][idx]) {
      idx = col;
    }
  }
  int* seam = VerticalSeamFiller(seams, idx);
  // delete seams
  for (int row = 0; row < height_; row++) {
    delete[] seams[row];
  }
  delete[] seams;
  return seam;
}

int* SeamCarver::VerticalSeamFiller(int**& seams, int idx) const {
  int* seam = new int[height_];
  seam[0] = idx;
  for (int row = 0; row < height_ - 1; row++) {
    if (idx == 0) {
      if (seams[row + 1][idx + 1] < seams[row + 1][idx]) {
        idx++;
      }
    } else if (idx == width_ - 1) {
      if (seams[row + 1][idx - 1] < seams[row + 1][idx]) {
        idx--;
      }
    } else {
      if (seams[row + 1][idx] <= seams[row + 1][idx - 1] &&
          seams[row + 1][idx] <= seams[row + 1][idx + 1]) {
        // do nothing since idx stays the same
      } else if (seams[row + 1][idx - 1] < seams[row + 1][idx] &&
                 seams[row + 1][idx - 1] <= seams[row + 1][idx + 1]) {
        idx--;
      } else if (seams[row + 1][idx + 1] < seams[row + 1][idx - 1] &&
                 seams[row + 1][idx + 1] < seams[row + 1][idx]) {
        idx++;
      }
    }
    seam[row + 1] = idx;
  }
  return seam;
}

void SeamCarver::RemoveHorizontalSeam() {
  std::cout << height_ << "}" << std::endl;
  int* to_remove = GetHorizontalSeam();
  image_.RemoveHorizontalSeam(to_remove);
  height_ = height_ - 1;
  delete[] to_remove;
}

void SeamCarver::RemoveVerticalSeam() {
  int* to_remove = GetVerticalSeam();
  image_.RemoveVerticalSeam(to_remove);
  width_ = width_ - 1;
  delete[] to_remove;
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
