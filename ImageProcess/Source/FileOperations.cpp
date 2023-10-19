#include "FileOperations.h"
#include <fstream>
#include <string>
#include <string_view>

void FileOperations::FileOperations::SanitizePath(std::string& filepath)
{
    filepath.erase(std::remove(filepath.begin(), filepath.end(), '\"'), filepath.end());
}

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

std::string FileOperations::FileOperations::GetFilenameWithExtension(const std::string& filepath)
{
    return std::filesystem::path(filepath).filename().string();
}

std::string FileOperations::FileOperations::GetDirectoryPath(const std::string& filepath)
{
    return std::filesystem::path(filepath).parent_path().string();
}

std::pair<std::optional<std::string>, bool> FileOperations::TGAFileOperation::ReadTGAFile(std::string_view filename, std::vector<uint8_t>& image, TGAHeader& header)
{
    //Start reading the TGA file 
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Started reading TGA file.");
    std::string ReadError;

    // Protect the original file with read only file format
    std::ifstream File(filename.data(), std::ios::in | std::ios::binary);
    //Return with error if unable to open the file
    if (!File.is_open()) {
        m_LogObj->LogMessage(Log::LogLevel::ERROR, "Unable to open the TGA file");
        ReadError =  "[Error]-> Failed to open input file.";
        return { ReadError, false };
    }

    File.read(reinterpret_cast<char*>(&header), sizeof(TGAHeader));
    //Return with error if unsupported file format is given
    if (header.image_type != 2) {
        m_LogObj->LogMessage(Log::LogLevel::ERROR, "Unsupported TGA image type");
        ReadError = "[Error]-> Unsupported TGA image type. Please convert your file in uncompressed true-color image format";
        return { ReadError, false };
    }

    image.resize(header.width * header.height * (header.pixel_depth / 8));

    //Read all the data 
    File.read(reinterpret_cast<char*>(image.data()), image.size());

    //Close the file after reading is complete
    File.close();
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Ended reading TGA file.");
    return { " ", true};
}

std::string FileOperations::TGAFileOperation::MakeUniqueFilename(const std::string& filename,const std::string& outputFileDir)
{
    // Check if the file already exists
    std::string OriginalPath = outputFileDir + "Blur_" + GetFilenameWithExtension(filename);

    if (!std::filesystem::exists(OriginalPath)) {
        return OriginalPath;  // The original filename is unique
    }

    std::filesystem::path Directory = std::filesystem::path(OriginalPath).parent_path();
    std::string FileNameStem = std::filesystem::path(OriginalPath).stem().string();
    std::string Extension = std::filesystem::path(OriginalPath).extension().string();
    int Count = 1;

    while (std::filesystem::exists(OriginalPath)) {
        std::string newFilename = FileNameStem + "_" + std::to_string(Count) + Extension;
        OriginalPath = (Directory / newFilename).string();
        Count++;
    }

    // Replace backslashes with forward slashes for portability
    std::replace(OriginalPath.begin(), OriginalPath.end(), '\\', '/');
    return OriginalPath;
}

std::pair<std::optional<std::string>, bool> FileOperations::TGAFileOperation::WriteTGAFile(std::string_view filename, std::string_view outputFileDir,
    const std::vector<uint8_t>& image, const TGAHeader& header, std::string& outputFileName)
{
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Started writing TGA file.");
    std::string WriteError;
    //Create unique name for the processed TGA file
    outputFileName = MakeUniqueFilename(filename.data(), outputFileDir.data());

    std::ofstream File(outputFileName, std::ios::out | std::ios::binary);
    //Return with error if somehow unable to open the output file, log it as well
    if (!File.is_open()) {
        m_LogObj->LogMessage(Log::LogLevel::ERROR, "Failed to create processed image");
        WriteError = "[Error]-> Failed to create blurred image on the given location.";
       return { WriteError, false };
    }

    File.write(reinterpret_cast<const char*>(&header), sizeof(TGAHeader));
    File.write(reinterpret_cast<const char*>(image.data()), image.size());
    //Close the file after writing into it
    File.close();
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Ended writing TGA file.");
    return { " ",true };
}



