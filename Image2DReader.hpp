#ifndef _IMAGE2DREADER_HPP_
#define _IMAGE2DREADER_HPP_
#include <iostream>
#include <string>
#include "Color.hpp"
#include "Image2D.hpp"

template <typename TValue>
class Image2DReader {
    public:
        typedef TValue Value;
        typedef Image2D<Value> Image;
        static bool read( Image & img, std::istream & input, bool ascii )
        {
            std::cerr << "[Image2DWriter<TValue>::read] NOT IMPLEMENTED." << std::endl;
            return false;
        }
};


/// Specialization for gray-level images.
template <>
class Image2DReader<unsigned char>{
    public:
        typedef unsigned char Value;
        typedef Image2D<Value> Image;
        static Image read (std::istream & input){
            std::string s;
            std::getline(input, s);
            int w, h, cmax;
            input >> w >> h >> cmax;
            Image img = Image(w , h);
            if(s[1] == '5'){
                char lect;
                input >> std::noskipws;
                for (int i=0; i < img.w(); i++){
                    for (int j=0; j < img.w(); j++){
                        input >> lect;
                        img.at(i,j) = lect;
                    }
                }
            }else{
                int lect;
                for (int i=0; i < img.w(); i++){
                    for (int j=0; j < img.w(); j++){
                        input >> lect;
                        img.at(i,j) = lect;
                    }
                }
            }
            return img;
        }
};


/// Specialization for color images.
template <>
class Image2DReader<Color> {
    public:
        typedef Color Value;
        typedef Image2D<Value> Image;
        static Image read( std::istream & input )
        {
            std::string s;
            std::string buf;
            std::getline(input, s);
            int w, h, cmax;
            input >> w;
            input >> h;
            input >> cmax;
            std::getline(input, buf);
            Image img = Image(w , h);
            if(s[1] == '6'){
                input >> std::noskipws;
                for (int i=0; i < img.w(); i++){
                    for (int j=0; j < img.w(); j++){
                        input >> img.at(j,i).red;
                        input >> img.at(j,i).green;
                        input >> img.at(j,i).blue;
                    }
                }
            }else{
                for (int i=0; i < img.w(); i++){
                    for (int j=0; j < img.w(); j++){
                        input >> img.at(j,i).red;
                        input >> img.at(j,i).green;
                        input >> img.at(j,i).blue;
                    }
                }
            }
            return img;
        }
};
#endif // _IMAGE2DREADER_HPP_
