#pragma once
#include "LogSystem.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

namespace Model
{
    class IModel
    {
    public:
        IModel() = default;
        virtual ~IModel() = default;
        virtual void ApplyBoxBlurfilter(std::vector<uint8_t>& image, int width, int height, int pixelDepth, float blurFactor) =0;
    };

    class ImageProcessingModel:public IModel
    {
       public:
           ImageProcessingModel(Log::LogSystem* logobj) :m_LogObj(logobj) {}
           void ApplyBoxBlurfilter(std::vector<uint8_t>& image, int width, int height, int pixelDepth, float blurFactor)override;

    private:
        Log::LogSystem* m_LogObj;
    };
}


