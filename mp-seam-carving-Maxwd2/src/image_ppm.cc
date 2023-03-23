#include "image_ppm.hpp"

// implement the rest of ImagePPM's functions here

std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  os << "P3\n"
     << image.GetWidth() << " " << image.GetHeight() << '\n'
     << image.GetMaxColorValue() << '\n';
  for (int row = 0; row < image.GetHeight(); row++) {
    for (int col = 0; col < image.GetWidth(); col++) {
      os << image.GetPixel(row, col).GetRed() << '\n';
      os << image.GetPixel(row, col).GetGreen() << '\n';
      os << image.GetPixel(row, col).GetBlue() << '\n';
    }
  }
  return os;
}

void ImagePPM::RemoveHorizontalSeam(int*& seam) {
  auto** new_image = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; row++) {
    new_image[row] = new Pixel[width_];
  }
  for (int col = 0; col < width_; col++) {
    int temp_row = 0;
    for (int row = 0; row < height_; row++) {
      if (seam[col] != row) {
        new_image[temp_row][col] = pixels_[row][col];
        temp_row++;
      }
    }
  }
  int temp_height = height_;
  int temp_width = width_;
  Clear();
  width_ = temp_width;
  height_ = temp_height;

  pixels_ = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; row++) {
    pixels_[row] = new Pixel[width_];
    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = new_image[row][col];
    }
    delete[] new_image[row];
  }
  delete[] new_image;

  height_ = height_ - 1;
}

void ImagePPM::RemoveVerticalSeam(int*& seam) {
  auto** new_image = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    new_image[row] = new Pixel[width_ - 1];
  }
  for (int row = 0; row < height_; row++) {
    int temp_col = 0;
    for (int col = 0; col < width_; col++) {
      if (seam[row] != col) {
        new_image[row][temp_col] = pixels_[row][col];
        temp_col++;
      }
    }
  }
  int temp_height = height_;
  int temp_width = width_;
  Clear();
  width_ = temp_width;
  height_ = temp_height;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_ - 1];
    for (int col = 0; col < width_ - 1; col++) {
      pixels_[row][col] = new_image[row][col];
    }
    delete[] new_image[row];
  }
  delete[] new_image;
  width_ = width_ - 1;
}

// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;
}