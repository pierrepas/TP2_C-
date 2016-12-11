#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"

int main(int argc, char* argv[] )
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;


    std::ifstream input(argv[1]);
    ColorImage2D img;
    Image2DReader<Color>::read(img, input);
    Iterator it = img.begin();

    for (ColorImage2D::Iterator it=img.begin(),
            it2=img.end(); it!=it2; it++ )
    {
        unsigned char tmp = it-> red;
        it-> red = it->blue;
        it->blue = tmp;
    }

    std::ofstream output( argv[2]);
    bool ok2 = Image2DWriter<Color>::write( img, output, false );
    if ( !ok2 ) {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

}

