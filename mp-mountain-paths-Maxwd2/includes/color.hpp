#ifndef COLOR_H
#define COLOR_H

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

class Color {
public:
  Color() = default;
  Color(int r, int g, int b);
  int Red() const { return red_; }
  int Green() const { return green_; }
  int Blue() const { return blue_; }

private:
  // bool ValidColorValue(int value) const;
  int red_ = 0;
  int green_ = 0;
  int blue_ = 0;
  static const int kMaxColorValue = 255;
  static const int kMinColorValue = 0;
};

bool operator==(const Color& rhs, const Color& lhs);

#endif