#include <iostream>
#include <fstream>
#include "Color.hpp"
#include "Image2D.hpp"
using namespace std;
int main( int argc, char** argv )
{

  typedef Image2D<Color> ColorImage2D;
  ColorImage2D img( 8, 8, Color( 255, 0, 255 ) );
  for ( int y = 0; y < img.h(); ++y )
    {
      for ( int x = 0; x < img.w(); ++x )
        std::cout << " " <<  img.at( x, y ).r() << img.at( x, y ).g() << img.at( x, y ).b(); // la conversion permet de voir les caractères sous forme d'entiers.
        std::cout << std::endl;
    }
  return 0;
}