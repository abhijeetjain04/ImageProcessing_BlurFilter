#pragma once

#include <fstream>
#include <filesystem>
#include <optional>


namespace FileOperations
{
	struct TGAHeader 
	{
		uint8_t id_length;
		uint8_t color_map_type;
		uint8_t image_type;
		uint16_t color_map_origin;
		uint16_t color_map_length;
		uint8_t color_map_depth;
		uint16_t x_origin;
		uint16_t y_origin;
		uint16_t width;
		uint16_t height;
		uint8_t pixel_depth;
		uint8_t image_descriptor;
	};

	class FileOperations
	{
	public:
		void checkFilepath(std::string& filepath);

		bool DoesFileExist(std::string& filepath);
		bool IsValidFilePath(std::string& filepath, std::string& errorMessage);
		bool IsTGAFile(std::string& filepath, std::string& errorMessage);
		void GetCompleteFilename(const std::string& filepath, std::string& completeFilename);
		void GetDirectoryPath(const std::string& filepath, std::string& directoryPath);
	};

	class TGAFileOperation:public FileOperations
	{
		std::pair<std::optional<std::string>, bool>  ReadTGAFile(const std::string& filename, std::vector<uint8_t>& image, TGAHeader& header);
		std::pair<std::optional<std::string>, bool> WriteTGAFile(const std::string& filename, const std::vector<uint8_t>& image, const TGAHeader& header);
	};
}
