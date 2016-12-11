#include "Histogramme.hpp"
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DWriter.hpp"
#include "Color.hpp"
#include "Image2DReader.hpp"
#include "Accessor.hpp"
using namespace std;

int main( int argc, char** argv ){
    typedef Image2D<Color> Image;
    if (argc < 3){
        std::cerr << "Utilisation: ./histogramme <nomFichierEntree> <nomFichierSortie" 
        << std::endl;
    }else{
        ifstream input( argv[1] );
        Image img;
        Image2DReader<Color>::read( img, input);

        Histogramme h;
        h.init(img.begin<ColorValueAccessor>(), img.end<ColorValueAccessor>());
        Image2D<unsigned char> c = h.getImage();

        ofstream output( argv[2] );
        Image2DWriter<unsigned char>::write( c, output, false );
        output.close();
    }
}


