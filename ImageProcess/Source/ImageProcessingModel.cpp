#include "ImageProcessingModel.h"

//Applying simple box blur
void Model::ImageProcessingModel::ApplyBoxBlurfilter(std::vector<uint8_t>& image, int width, int height, int pixelDepth, float blurFactor)
{
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Start applying blur filter");

    if (blurFactor <= 0.0) {
        return;  // No blur
    }

    //Calculate the size of the blur based on the blur factor
    int BlurSize = static_cast<int>(std::round(10.0 * blurFactor));

    //Calculate the ChannelCount for TGA image for 24 bit it will be 3 and for 32 bit it will be 4 
    int ChannelCount = pixelDepth / 8;

   // Loop through each pixel in the image
   for (int y = 0; y < height; y++) 
   {
       for (int x = 0; x < width; x++) 
       {
           //Initialize accumulators for each color channel and the count of pixels
           int RedSum = 0;
           int GreenSum = 0;
           int BlueSum = 0;
           int AlphaSum = 0;
           int NumPixels = 0;
           int PixelX =0;
           int PixelY=0;

           //Iterate through a neighborhood of pixels centered around the current pixel
           for (int dy = -BlurSize; dy <= BlurSize; dy++)
           {
               for (int dx = -BlurSize; dx <= BlurSize; dx++) 
               {
                   //Calculate the X and Y coordinates of the neighboring pixel
                    PixelX = x + dx;
                    PixelY = y + dy;

                   //Check if the neighboring pixel is within the image boundaries
                   if (PixelX >= 0 && PixelX < width && PixelY >= 0 && PixelY < height) 
                   {
                      //Calculate the index of the neighboring pixel in the image vector
                      int index = (PixelY * width + PixelX) * ChannelCount;

                      //Accumulate the color channel values for the neighboring pixel
                      RedSum += image[index];
                      GreenSum += image[index + 1];
                      BlueSum += image[index + 2];
                      //Calculate alpha sum if 32 bit image
                      if (ChannelCount == 4)
                      {
                       AlphaSum += image[index + 3];
                      }
                      //Increment the count of pixels in the neighborhood
                      NumPixels++;
                   }
               }
           }
           //Calculate the new color values for the current pixel based on the average
           int PixelIndex = (y * width + x) * ChannelCount;

           //Update the pixel with the averaged color values
           if (NumPixels > 0) {
               image[PixelIndex] = static_cast<uint8_t>(RedSum / NumPixels);
               image[PixelIndex + 1] = static_cast<uint8_t>(GreenSum / NumPixels);
               image[PixelIndex + 2] = static_cast<uint8_t>(BlueSum / NumPixels);
               //Update the alpha value if image is 32 bit
               if (ChannelCount == 4)
               {
                  image[PixelIndex + 3] = static_cast<uint8_t>(AlphaSum / NumPixels);
               }
           }
       }
   }
   m_LogObj->LogMessage(Log::LogLevel::INFO, "Completed blurring process");
}


