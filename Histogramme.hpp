
#include <vector>
#include "Image2D.hpp"

class Histogramme{
	typedef Image2D<unsigned char> GrayImage;
	std::vector<float> h1;
	std::vector<float> hC1;

public:
    template <typename InputIterator>
    void init(InputIterator it, InputIterator itE){
        float valeur = 0.0;
        for (; it != itE; ++it){
            h1.push_back(valeur);
            valeur += 1.0;
        }

        for (int i = 0; i < 256; i++){
            h1[i] /= (valeur);
        }

        hC1[0] = h1[0];
        for (int i = 1; i < 256; i++){
            hC1[i] = hC1[i - 1] + h1[i];
        }
    }

    GrayImage getImage() const{
        GrayImage img(512, 256);
        for (GrayImage::Iterator it = img.begin(), itE = img.end(); it != itE; it++){
            *it = 255;
        }

        double maxVal = getValMax();
        for (int i = 0; i < 256; i++){
            for (int j = 0; j < (int)((h1[i] * (255.0/maxVal))); j++){
                img.at(i, 255 - j) = 0;
            }
        }

        for (int i = 256; i < 512; i++){
            for (int j = 0; j < (int)(hC1[i%256] * 255.0); j++){
                img.at(i, 255 - j) = 0;
            }
        }
        return img;
    }

    double getValMax() const{
        double max = 0.0;
        for (int i = 0; i < 256; i++){
            if (h1[i] > max){
                max = h1[i];
            }
        }
        return max;
    }
};