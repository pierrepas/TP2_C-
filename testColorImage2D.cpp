#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"
int main()
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;
    ColorImage2D img( 256, 256, Color( 0, 0, 0 ) );
    Iterator it = img.begin();
    for ( int y = 0; y < 256; ++y )
        for ( int x = 0; x < 256; ++x )
        {
            *it++ = Color( y, x, (2*x+2*y) % 256 );
        }
    std::ofstream output( "colors.ppm");

    /*
       output << "P6" << std::endl; // PPM raw
       output << "# Generated by You !" << std::endl;
       output << img.w() << " " << img.h() << std::endl;
       output << "255" << std::endl;
       const ColorImage2D& cimg = img; // Vue "constante" sur l'image img.
       for ( ConstIterator it = cimg.begin(), itE = cimg.end(); it != itE; ++it  ) // (*)
       {
       Color c = *it;
       output << c.red << c.green << c.blue;
       }
       output.close();
       return 0;
       */

    bool ok2 = Image2DWriter<Color>::write( img, output, false );
    if ( !ok2 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    std::ifstream input("colors.ppm");
    ColorImage2D imgRD2 = Image2DReader<Color>::read(input);
    std::ofstream output_2("colors_2.ppm");
    bool ok3 = Image2DWriter<Color>::write( imgRD2, output_2, false );
    if ( !ok3 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output_2.close();

}

