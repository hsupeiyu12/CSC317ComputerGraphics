#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code from computer-graphics-raster-images
    assert(
      (num_channels == 3 || num_channels ==1 ) &&
      ".ppm only supports RGB or grayscale images");
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
      

      using namespace std;
      ofstream ofs(filename, ios_base::out | ios_base::binary);
      if (num_channels == 3)
          ofs << "P6" << endl << width << ' ' << height << endl << "255" << endl;
      else
          ofs << "P5" << endl << width << ' ' << height << endl << "255" << endl;

      for (std::vector<unsigned char>::const_iterator it = data.begin() ; it != data.end(); ++it){
          ofs << *it;
      }

      ofs.close();
    
      return true;

  ////////////////////////////////////////////////////////////////////////////
}
