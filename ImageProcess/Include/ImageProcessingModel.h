#pragma once
#include "LogSystem.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

namespace Model
{
    class ImageProcessingModel
    {
       public:
           ImageProcessingModel(Log::LogSystem* logobj) :m_LogObj(logobj) {}
           void ApplyBlur(std::vector<uint8_t>& image, int width, int height, int pixelDepth, float blurFactor);

    private:
        Log::LogSystem* m_LogObj;
    };
}


