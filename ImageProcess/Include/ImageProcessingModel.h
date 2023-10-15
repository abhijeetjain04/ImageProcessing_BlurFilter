#pragma once
#include <iostream>

#include <vector>
#include <cstdint>
#include <cmath>

# define M_PI           3.14159265358979323846 


namespace Model
{
    class ImageProcessingModel
    {
       public:
           void ApplyBlur(std::vector<uint8_t>& image, int width, int height, int pixelDepth, float blurFactor);
    };
}


