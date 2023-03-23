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
#include "path_image.hpp"

int main(int argc, char** argv) {
  argc++;
  /*Color c(5, 19, 100);
  std::cout << c.Red() << std::endl;
  Path p(5, 2);
  p.IncEleChange(10);
  std::cout << p.EleChange() << " " << p.Length() << std::endl;*/
  std::string word = argv[1];
  /* ElevationDataset e = ElevationDataset(word, 5, 3);
   for (const std::vector<int>& vect1 : e.GetData()) {
     for (int i : vect1) {
       std::cout << " " << i;
     }
     std::cout << '\n';
   }
   std::cout << e.DatumAt(0, 2) << std::endl;

   GrayscaleImage g = GrayscaleImage(e);
   std::cout << g.ColorAt(0, 2).Blue() << " " << g.ColorAt(0, 2).Green() << " "
             << g.ColorAt(0, 2).Red() << std::endl;

   PathImage p = PathImage(g, e);
   for (const Path& p : p.Paths()) {
     for (size_t ele : p.GetPath()) {
       std::cout << " " << ele;
     }
     std::cout << '\n';
   }
   std::cout << p.BestPathRow() << std::endl;
   for (size_t i = 0; i < p.Height(); i++) {
     for (size_t j = 0; j < p.Width(); j++) {
       std::cout << p.GetPathImage().at(i).at(j).Red() << ", "
                 << p.GetPathImage().at(i).at(j).Green() << ", "
                 << p.GetPathImage().at(i).at(j).Blue() << "    ";
     }
     std::cout << '\n';
   } */
  ElevationDataset e = ElevationDataset(word, 51, 55);

  for (const std::vector<int>& vect1 : e.GetData()) {
    for (int i : vect1) {
      std::cout << " " << i;
    }
    std::cout << '\n';
  }

  GrayscaleImage g = GrayscaleImage(e);
  PathImage p = PathImage(g, e);

  for (size_t i = 0; i < p.Height(); i++) {
    std::cout << p.Paths().at(i).EleChange() << std::endl;
  }
  std::cout << "Best path at index: " << p.BestPathRow() << '\n';

  g.ToPpm("gray-image.ppm");
  std::cout << " is ready!" << '\n';
  p.ToPpm("color-image.ppm");
  std::cout << " is ready!" << '\n';
}

// bin/exec example-data/ex_input_data/prompt_5w_2h.dat
// bin/exec example-data/ex_input_data/map-input-w844-h480.dat
// bin/exec example-data/ex_input_data/map-input-w480-h480.dat
// bin/exec example-data/ex_input_data/map-input-w51-h55.dat
// bin/exec example-data/ex_input_data/all-tie-row1-2w-3h.dat
/*
 /home/vagrant/src/mp-mountain-paths-Maxwd2/example-data/ex_input_data/prompt_5w_2h.dat
*/