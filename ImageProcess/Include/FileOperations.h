#pragma once
#include <filesystem>
#include <optional>
#include <utility>

namespace FileOperations
{
#pragma pack(push, 1)
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
#pragma pack(pop)

	class FileOperations
	{
	public:
		bool DoesFileExist(std::string_view filepath);
		bool IsValidFilePath(std::string& filepath);
		bool IsValidFolderPath(std::string& folderepath);
		bool IsTGAFile(std::string_view filepath);
		std::string GetCompleteFilename(const std::string& filepath);
		std::string GetDirectoryPath(const std::string& filepath);
	};

	class TGAFileOperation:public FileOperations
	{
	public:
		std::pair<std::optional<std::string>, bool> ReadTGAFile(std::string_view filename, std::vector<uint8_t>& image, TGAHeader& header);
		std::pair<std::optional<std::string>, bool> WriteTGAFile(std::string_view filename, std::string_view outputFileDir, const std::vector<uint8_t>& image,
			const TGAHeader& header, std::string& outputFileName);
	private:
		std::string MakeUniqueFilename(const std::string& filePath,const std::string& outputFileDir);
		std::string m_OutPutDir;
	};
}
