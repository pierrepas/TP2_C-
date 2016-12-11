// save-green-channel.cpp
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include "Image2D.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"

#define DEBUG 1

using namespace std;
int main( int argc, char** argv ){
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef ColorImage2D::Iterator ColorIterator;
    if ( argc < 2 ) 
        { 
            std::cerr << "Usage: save-channels <input.ppm>" << std::endl;
            return 0;
        }

    std::string filename = argv[1];
    ColorImage2D imgRead;
    std::ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read( imgRead, input );
    if ( !ok )
        {
            std::cerr << "Error reading input file." << std::endl;
            return 1;
        }
    input.close();

    ColorImage2D const img = imgRead;
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    GrayLevelImage2D imgR( img.w(), img.h() );
    GrayLevelImage2D imgG( img.w(), img.h() );
    GrayLevelImage2D imgB( img.w(), img.h() );

    if(DEBUG)
        std::cerr << "Création des images terminée" << std::endl;

    typedef ColorImage2D::GenericConstIterator< ColorGreenAccessor > ColorGreenConstIterator;
    typedef ColorImage2D::GenericConstIterator< ColorRedAccessor > ColorRedConstIterator;
    typedef ColorImage2D::GenericConstIterator< ColorBlueAccessor > ColorBlueConstIterator;

    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();
    ColorRedConstIterator itRed = img.begin< ColorRedAccessor >();
    ColorBlueConstIterator itBlue = img.begin< ColorBlueAccessor >();

    GrayLevelIterator itR = imgG.begin();
    GrayLevelIterator itB = imgB.begin();
    for ( GrayLevelIterator it = imgR.begin(), itE = imgR.end();
          it != itE; ++it, ++itR, ++itB )
        {
            *it = *itGreen;
            *itR = *itRed;
            *itB = *itBlue;
            ++itGreen;
            ++itRed;
            ++itBlue;
        }

    if(DEBUG)
        std::cerr << "Lecture Terminée" << std::endl;

    std::ofstream output("papillon_red.pgm");

    bool ok2 = GrayLevelImage2DWriter::write( imgR, output, false );
    if ( !ok2 )
        {
            std::cerr << "Error writing output file." << std::endl;
            return 1;
        }
    output.close();

    output.open("papillon_green.pgm");
    ok2 = GrayLevelImage2DWriter::write( imgG, output, false );
    if ( !ok2 )
        {
            std::cerr << "Error writing output file." << std::endl;
            return 1;
        }
    output.close();

    output.open("papillon_blue.pgm");
    ok2 = GrayLevelImage2DWriter::write( imgB, output, false );
    if ( !ok2 )
        {
            std::cerr << "Error writing output file." << std::endl;
            return 1;
        }
    output.close();

    if(DEBUG)
        std::cerr << "Écriture Terminée" << std::endl;

    return 0;
}
