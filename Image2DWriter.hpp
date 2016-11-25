#ifndef _IMAGE2DWRITER_HPP_
#define _IMAGE2DWRITER_HPP_
#include <iostream>
#include <string>
#include "Color.hpp"
#include "Image2D.hpp"

template <typename TValue>
class Image2DWriter {
    public:
        typedef TValue Value;
        typedef Image2D<Value> Image;
        static bool write( Image & img, std::ostream & output, bool ascii )
        {
            std::cerr << "[Image2DWriter<TValue>::write] NOT IMPLEMENTED." << std::endl;
            return false;
        }
};


/// Specialization for gray-level images.
template <>
class Image2DWriter<unsigned char> {
    public:
        typedef unsigned char Value;
        typedef Image2D<Value> Image;
        static bool write( Image & img, std::ostream & output, bool ascii )
        {
            if (ascii){
                output << "P2";
            }
            else {
                output << "P5";
            }
            output << std::endl << img.h() << " " << img.w() << std::endl;
            output << 255 << std::endl;

            for ( int i = 0; i < img.h(); i++){
                for (int j = 0; j < img.w(); j++){
                    if (ascii){

                        output << (int) img.at(i, j);
                    }
                    else {
                        output << (char) img.at(i, j);
                    }
                }
            }
            return true;
        }
};


/// Specialization for color images.
template <>
class Image2DWriter<Color> {
    public:
        typedef Color Value;
        typedef Image2D<Value> Image;
        static bool write( Image & img, std::ostream & output, bool ascii )
        {
            if (ascii){
                output << "P3";
            }
            else {
                output << "P6";
            }
            output << std::endl << img.w() << " " << img.h() << std::endl;
            output << 255 << std::endl;

            if (!ascii){
                for( Image::Iterator it=img.begin(), itE = img.end(); it!=itE; ++it )
                {
                    output << it->red << it->green << it->blue;
                }
            }
            return true;
        }
};
#endif // _IMAGE2DWRITER_HPP_
