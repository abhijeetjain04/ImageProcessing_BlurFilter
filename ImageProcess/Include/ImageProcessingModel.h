#pragma once
#include <iostream>

#include <vector>
#include <cstdint>
#include <cmath>

namespace Model
{
    class ImageProcessingModel
    {
       public:
           void ApplyBlur(std::vector<uint8_t>& image, int width, int height, int pixelDepth, float blurFactor);
    private:
        void 
    };
}


