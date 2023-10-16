#include "FileOperations.h"
#include <fstream>
#include <string>
#include <string_view>

bool FileOperations::FileOperations::DoesFileExist(std::string_view filepath)
{
    return std::filesystem::exists(filepath.data());
}

bool FileOperations::FileOperations::IsValidFilePath(std::string& filepath)
{
    if (DoesFileExist(filepath))
    {
        std::replace(filepath.begin(), filepath.end(), '\\', '/');
        return true;
    }
    filepath.clear();
    return false;
}

bool FileOperations::FileOperations::IsValidFolderPath(std::string& folderepath)
{
    if (std::filesystem::is_directory(folderepath))
    {
        std::replace(folderepath.begin(), folderepath.end(), '\\', '/');
        return true;
    }
    return false;
}

bool FileOperations::FileOperations::IsTGAFile(std::string_view filepath)
{
    if (std::filesystem::path(filepath.data()).extension() == ".tga")
    {
        return true;
    }
    return false;
}



std::string FileOperations::FileOperations::GetCompleteFilename(const std::string& filepath)
{
    return std::filesystem::path(filepath).filename().string();
}

std::string FileOperations::FileOperations::GetDirectoryPath(const std::string& filepath)
{
    return std::filesystem::path(filepath).parent_path().string();
}

std::pair<std::optional<std::string>, bool> FileOperations::TGAFileOperation::ReadTGAFile(std::string_view filename, std::vector<uint8_t>& image, TGAHeader& header)
{
    std::string error;
    std::ifstream file(filename.data(), std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        error =  "Failed to open file.";
        return { error, false };
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(TGAHeader));

    if (header.image_type != 2) {
        error = "Unsupported TGA image type.";
        return { error, false };
    }

    image.resize(header.width * header.height * (header.pixel_depth / 8));
    file.read(reinterpret_cast<char*>(image.data()), image.size());
    file.close();
    return { " ", true};
}

std::string FileOperations::TGAFileOperation::MakeUniqueFilename(const std::string& filename,const std::string& outputFileDir)
{
    // Check if the file already exists
    std::string originalPath = outputFileDir + "Blur_" + GetCompleteFilename(filename);

    if (!std::filesystem::exists(originalPath)) {
        return originalPath;  // The original filename is unique
    }

    std::filesystem::path directory = std::filesystem::path(originalPath).parent_path();
    std::string filenameStem = std::filesystem::path(originalPath).stem().string();
    std::string extension = std::filesystem::path(originalPath).extension().string();
    int count = 1;

    while (std::filesystem::exists(originalPath)) {
        std::string newFilename = filenameStem + "_" + std::to_string(count) + extension;
        originalPath = (directory / newFilename).string();
        count++;
    }

    // Replace backslashes with forward slashes for portability
    std::replace(originalPath.begin(), originalPath.end(), '\\', '/');
    return originalPath;
}

std::pair<std::optional<std::string>, bool> FileOperations::TGAFileOperation::WriteTGAFile(std::string_view filename, std::string_view outputFileDir,
    const std::vector<uint8_t>& image, const TGAHeader& header, std::string& outputFileName)
{
    std::string error;
    outputFileName = MakeUniqueFilename(filename.data(), outputFileDir.data());

    std::ofstream file(outputFileName, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
       error = "Failed to create file.";
       return { error, false };
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(TGAHeader));
    file.write(reinterpret_cast<const char*>(image.data()), image.size());
    file.close();
    return { " ",true };
}



