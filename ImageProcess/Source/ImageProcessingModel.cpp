#include "ImageProcessingModel.h"

/*
bool readTGA(const std::string& filename, std::vector<uint8_t>& image, Model::TGAHeader& header) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&header), sizeof( Model::TGAHeader));


    if (header.image_type != 2) {
        // we may need to support Uncompressed Color-Mapped Image (Color-Indexed Image):
        //Uncompressed Black-and-White (Grayscale) Image:
        std::cerr << "Unsupported TGA image type: " << static_cast<int>(header.image_type) << std::endl;
        return false;
    }

    //`width * height`: This represents the total number of pixels in the image.
    auto total_pixels = header.width * header.height;
    //`pixel_depth / 8`: This converts the pixel depth(measured in bits per pixel) into bytes.
    auto size_byte = header.pixel_depth / 8;
    auto final_size = header.width * header.height * (header.pixel_depth / 8);
    image.resize(header.width * header.height * (header.pixel_depth / 8));
    file.read(reinterpret_cast<char*>(image.data()), image.size());

    return true;
}

bool writeTGA(const std::string& filename, const std::vector<uint8_t>& image, const  Model::TGAHeader& header) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to create file: " << filename << std::endl;
        return false;
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(Model::TGAHeader));
    file.write(reinterpret_cast<const char*>(image.data()), image.size());

    return true;
}

void applyBlur(std::vector<uint8_t>& image, int width, int height, float blurFactor) {
    if (blurFactor <= 0.0) {
        return;  // No blur
    }

    int blurSize = static_cast<int>(std::round(10.0 * blurFactor));

    std::vector<uint8_t> blurredImage(image.size());

    for (int y = blurSize; y < height - blurSize; ++y) {
        for (int x = blurSize; x < width - blurSize; ++x) {
            for (int c = 0; c < 3; ++c) {
                int sum = 0;
                for (int dx = -blurSize; dx <= blurSize; ++dx) {
                    for (int dy = -blurSize; dy <= blurSize; ++dy) {
                        sum += image[3 * ((y + dy) * width + (x + dx)) + c];
                    }
                }
                blurredImage[3 * (y * width + x) + c] = sum / ((2 * blurSize + 1) * (2 * blurSize + 1));
            }
        }
    }

    image = blurredImage;
}

void applyBlur(std::vector<uint8_t>& image, int width, int height, float blurFactor)
{
    if (blurFactor <= 0.0) {
        return;  // No blur
    }
    // Calculate the blur size based on the blur factor
    int blurSize = static_cast<int>(std::round(10.0 * blurFactor));

    // Iterate through the image pixels
    for (int y = blurSize; y < height - blurSize; y++) {
        for (int x = blurSize; x < width - blurSize; x++) {
            // Initialize color accumulators for each channel
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;

            // Iterate through neighboring pixels within the blur size
            for (int dy = -blurSize; dy <= blurSize; dy++) {
                for (int dx = -blurSize; dx <= blurSize; dx++) {
                    // Calculate the index of the current pixel
                    int index = ((y + dy) * width + (x + dx)) * 3;

                    // Accumulate the color channel values
                    redSum += image[index];
                    greenSum += image[index + 1];
                    blueSum += image[index + 2];
                }
            }

            // Calculate the number of pixels in the neighborhood
            int numPixels = (2 * blurSize + 1) * (2 * blurSize + 1);

            // Update the pixel with the averaged color values
            int pixelIndex = (y * width + x) * 3;
            image[pixelIndex] = static_cast<uint8_t>(redSum / numPixels);
            image[pixelIndex + 1] = static_cast<uint8_t>(greenSum / numPixels);
            image[pixelIndex + 2] = static_cast<uint8_t>(blueSum / numPixels);
        }
    }
}

*/

/*
void Model::ImageProcessingModel::ApplyBlur(std::vector<uint8_t>& image, int width, int height, int pixelDepth, float blurFactor)
{
    //Applying simple box blur
    if (blurFactor <= 0.0) {
        return;  // No blur
    }

    // 1. Calculate the size of the blur based on the blur factor
    int blurSize = static_cast<int>(std::round(10.0 * blurFactor));

    // Example code for applying blur to a 24-bit image
    if (pixelDepth == 24)
    {
        // Apply blur effect to a 24-bit image
            // 2. Loop through each pixel in the image
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {

                // 3. Initialize accumulators for each color channel and the count of pixels
                int redSum = 0;
                int greenSum = 0;
                int blueSum = 0;
                int numPixels = 0;

                // 4. Iterate through a neighborhood of pixels centered around the current pixel
                for (int dy = -blurSize; dy <= blurSize; dy++) {
                    for (int dx = -blurSize; dx <= blurSize; dx++) {
                        // 5. Calculate the X and Y coordinates of the neighboring pixel
                        int pixelX = x + dx;
                        int pixelY = y + dy;

                        // 6. Check if the neighboring pixel is within the image boundaries
                        if (pixelX >= 0 && pixelX < width && pixelY >= 0 && pixelY < height) {
                            // 7. Calculate the index of the neighboring pixel in the image vector
                            int index = (pixelY * width + pixelX) * 3;
                            // 8. Accumulate the color channel values for the neighboring pixel
                            redSum += image[index];
                            greenSum += image[index + 1];
                            blueSum += image[index + 2];
                            // 9. Increment the count of pixels in the neighborhoo
                            numPixels++;
                        }
                    }
                }
                // 10. Calculate the new color values for the current pixel based on the average
                int pixelIndex = (y * width + x) * 3;

                // Update the pixel with the averaged color values
                if (numPixels > 0) {
                    image[pixelIndex] = static_cast<uint8_t>(redSum / numPixels);
                    image[pixelIndex + 1] = static_cast<uint8_t>(greenSum / numPixels);
                    image[pixelIndex + 2] = static_cast<uint8_t>(blueSum / numPixels);
                }
            }
        }
    }
    // Example code for applying blur to a 32-bit image
    else if (pixelDepth == 32)
    {
        int channelCount = pixelDepth / 8;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int redSum = 0;
                int greenSum = 0;
                int blueSum = 0;
                int alphaSum = 0;
                int numPixels = 0;

                for (int dy = -blurSize; dy <= blurSize; dy++) {
                    for (int dx = -blurSize; dx <= blurSize; dx++) {
                        int pixelX = x + dx;
                        int pixelY = y + dy;

                        if (pixelX >= 0 && pixelX < width && pixelY >= 0 && pixelY < height) {
                            int index = (pixelY * width + pixelX) * channelCount;

                            redSum += image[index];
                            greenSum += image[index + 1];
                            blueSum += image[index + 2];
                            alphaSum += image[index + 3];
                            numPixels++;
                        }
                    }
                }

                int pixelIndex = (y * width + x) * channelCount;

                if (numPixels > 0)
                {
                    image[pixelIndex] = static_cast<uint8_t>(redSum / numPixels);
                    image[pixelIndex + 1] = static_cast<uint8_t>(greenSum / numPixels);
                    image[pixelIndex + 2] = static_cast<uint8_t>(blueSum / numPixels);
                    image[pixelIndex + 3] = static_cast<uint8_t>(alphaSum / numPixels);
                }
            }
        }

    }

}
*/

void Model::ImageProcessingModel::ApplyBlur(std::vector<uint8_t>& image, int width, int height, int pixelDepth, float blurFactor)
{
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Applying blur");
    //Applying simple box blur
    if (blurFactor <= 0.0) {
        return;  // No blur
    }

    // 1. Calculate the size of the blur based on the blur factor
    int BlurSize = static_cast<int>(std::round(10.0 * blurFactor));

    // Example code for applying blur to a 24-bit image
    int ChannelCount = pixelDepth / 8;
   // Apply blur effect to a 24-bit image
       // 2. Loop through each pixel in the image
   for (int y = 0; y < height; y++) 
   {
       for (int x = 0; x < width; x++) 
       {
           // 3. Initialize accumulators for each color channel and the count of pixels
           int RedSum = 0;
           int GreenSum = 0;
           int BlueSum = 0;
           int AlphaSum = 0;
           int NumPixels = 0;
           int PixelX =0;
           int PixelY=0;

           // 4. Iterate through a neighborhood of pixels centered around the current pixel
           for (int dy = -BlurSize; dy <= BlurSize; dy++)
           {
               for (int dx = -BlurSize; dx <= BlurSize; dx++) 
               {
                   // 5. Calculate the X and Y coordinates of the neighboring pixel
                    PixelX = x + dx;
                    PixelY = y + dy;

                   // 6. Check if the neighboring pixel is within the image boundaries
                   if (PixelX >= 0 && PixelX < width && PixelY >= 0 && PixelY < height) 
                   {
                      // 7. Calculate the index of the neighboring pixel in the image vector
                      int index = (PixelY * width + PixelX) * ChannelCount;

                      // 8. Accumulate the color channel values for the neighboring pixel
                      RedSum += image[index];
                      GreenSum += image[index + 1];
                      BlueSum += image[index + 2];
                      if (ChannelCount == 4)
                      {
                       AlphaSum += image[index + 3];
                      }
                      // 9. Increment the count of pixels in the neighborhood
                      NumPixels++;
                   }
               }
           }
           // 10. Calculate the new color values for the current pixel based on the average
           int PixelIndex = (y * width + x) * ChannelCount;

           // Update the pixel with the averaged color values
           if (NumPixels > 0) {
               image[PixelIndex] = static_cast<uint8_t>(RedSum / NumPixels);
               image[PixelIndex + 1] = static_cast<uint8_t>(GreenSum / NumPixels);
               image[PixelIndex + 2] = static_cast<uint8_t>(BlueSum / NumPixels);
               if (ChannelCount == 4)
               {
                  image[PixelIndex + 3] = static_cast<uint8_t>(AlphaSum / NumPixels);
               }
           }
       }
   }
}


