#include "grayscale_image.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  std::string temp;
  for (size_t i = 0; i < dataset.Height(); i++) {
    std::vector<Color> vect;
    for (size_t j = 0; j < dataset.Width(); j++) {
      // double double_color_num = 0;
      int int_color_num = 0;
      temp = "";
      if (dataset.MinEle() != dataset.MaxEle()) {
        double min_ele = dataset.MinEle();
        double max_ele = dataset.MaxEle();
        double elevation_point = dataset.DatumAt(i, j);
        int_color_num = (int)std::round(
            ((elevation_point - min_ele) / (max_ele - min_ele)) *
            kMaxColorValue);
      }
      vect.push_back(Color(int_color_num, int_color_num, int_color_num));
    }
    image_.push_back(vect);
    vect.clear();
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  GrayscaleImage g = GrayscaleImage(ElevationDataset(filename, width, height));
  width_ = g.Width();
  height_ = g.Height();
  image_ = g.GetImage();
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  size_t new_row = row;
  size_t new_col = col;
  if (new_row > height_ - 1 || new_col > width_ - 1 || new_row < 0 ||
      new_col < 0) {
    throw std::invalid_argument("Invalid index for ColorAt()");
  }
  return image_.at(row).at(col);
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << '\n' << width_ << " " << height_ << '\n' << "255" << '\n';
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      ofs << image_[i][j].Red() << " " << image_[i][j].Green() << " "
          << image_[i][j].Blue() << " ";
    }
    ofs << '\n';
  }
  std::cout << name;
}