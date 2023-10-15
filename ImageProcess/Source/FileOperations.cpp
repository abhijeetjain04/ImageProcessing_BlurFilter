#include "FileOperations.h"

void FileOperations::FileOperations::checkFilepath(std::string& filepath)
{
  
}

bool FileOperations::FileOperations::DoesFileExist(std::string& filepath)
{
    return std::filesystem::exists(filepath);
}

bool FileOperations::FileOperations::IsValidFilePath(std::string& filepath, std::string& errorMessage)
{
    if (DoesFileExist(filepath))
    {
        std::replace(filepath.begin(), filepath.end(), '\\', '/');
        errorMessage.clear();
        return true;
    }

    errorMessage = "Invalid input. Please enter the correct path again.";
    filepath.clear();
    return false;
}

bool FileOperations::FileOperations::IsTGAFile(std::string& filepath, std::string& errorMessage)
{
    if (std::filesystem::path(filepath).extension() == ".tga")
    {
        return true;
    }
    else
    {
        errorMessage = "File is not tga.Please enter the tga file path again.";
        return false;
    }
}

void FileOperations::FileOperations::GetCompleteFilename(const std::string& filepath, std::string& completeFilename)
{
    completeFilename = std::filesystem::path(filepath).filename().string();
}

void FileOperations::FileOperations::GetDirectoryPath(const std::string& filepath, std::string& directoryPath)
{
    directoryPath = std::filesystem::path(filepath).parent_path().string();
}

std::pair<std::optional<std::string>, bool> FileOperations::TGAFileOperation::ReadTGAFile(const std::string& filename, std::vector<uint8_t>& image, TGAHeader& header)
{
    std::string error;
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        error =  "Failed to open file: ";
        return { error, false };
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(TGAHeader));


    if (header.image_type != 2) {
        // we may need to support Uncompressed Color-Mapped Image (Color-Indexed Image):
        //Uncompressed Black-and-White (Grayscale) Image:
        error = "Unsupported TGA image type: ";
        return { error, false };
    }

    ////`width * height`: This represents the total number of pixels in the image.
    //auto total_pixels = header.width * header.height;
    ////`pixel_depth / 8`: This converts the pixel depth(measured in bits per pixel) into bytes.
    //auto size_byte = header.pixel_depth / 8;
    //auto final_size = header.width * header.height * (header.pixel_depth / 8);
    //image.resize(header.width * header.height * (header.pixel_depth / 8));
    file.read(reinterpret_cast<char*>(image.data()), image.size());

    return { " ", true};
}

std::pair<std::optional<std::string>, bool> FileOperations::TGAFileOperation::WriteTGAFile(const std::string& filename, const std::vector<uint8_t>& image, const TGAHeader& header)
{
    std::string error;
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
       error = "Failed to create file: ";
       return { error, false };
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(TGAHeader));
    file.write(reinterpret_cast<const char*>(image.data()), image.size());

    return { " ",true };
}
