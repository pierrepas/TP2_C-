#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
int main()
{
  typedef Image2D<Color> ColorImage2D;
  typedef ColorImage2D::Iterator Iterator;
  ColorImage2D img( 256, 256, Color( 0, 0, 0 ) );
  Iterator it = img.begin();
  for ( int y = 0; y < 256; ++y )
    for ( int x = 0; x < 256; ++x )
      {
        *it++ = Color( y, x, (2*x+2*y) % 256 );
      }
  std::ofstream output( "colors.ppm");
  output << "P6" << std::endl; // PPM raw
  output << "# Generated by You !" << std::endl;
  output << img.w() << " " << img.h() << std::endl;
  output << "255" << std::endl;
  for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it ) // (*)
    { 
      Color c = *it;
      output << c.red << c.green << c.blue;
    }
  output.close();
  return 0;
}