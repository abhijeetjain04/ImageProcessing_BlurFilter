#pragma once
#include "LogSystem.h"
#include <filesystem>
#include <optional>
#include <utility>

namespace FileOperations
{
	class IFileOperation
	{
	public:
		IFileOperation() = default;
		virtual ~IFileOperation() = default;

		virtual bool DoesFileExist(std::string_view filepath) = 0;
		virtual bool IsValidFilePath(std::string& filepath) = 0;
		virtual bool IsValidFolderPath(std::string& folderepath) = 0;
		virtual std::string GetFilenameWithExtension(const std::string& filepath) = 0;
		virtual std::string GetDirectoryPath(const std::string& filepath) = 0;
	};

	class FileOperations :public IFileOperation
	{
	public:
		FileOperations(Log::LogSystem* logobj) :m_LogObj(logobj) {}
		void SanitizePath(std::string& filepath);
		bool DoesFileExist(std::string_view filepath) override;
		bool IsValidFilePath(std::string& filepath)override;
		bool IsValidFolderPath(std::string& folderepath)override;
		bool IsTGAFile(std::string_view filepath);
		std::string GetFilenameWithExtension(const std::string& filepath)override;
		std::string GetDirectoryPath(const std::string& filepath)override;
	private:
		Log::LogSystem* m_LogObj;
	};

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

	class TGAFileOperation:public FileOperations
	{
	public:
		TGAFileOperation(Log::LogSystem* logobj) :m_LogObj(logobj), FileOperations(m_LogObj){}
		std::pair<std::optional<std::string>, bool> ReadTGAFile(std::string_view filename, std::vector<uint8_t>& image, TGAHeader& header);
		std::pair<std::optional<std::string>, bool> WriteTGAFile(std::string_view filename, std::string_view outputFileDir, const std::vector<uint8_t>& image,
			const TGAHeader& header, std::string& outputFileName);
	private:
		std::string MakeUniqueFilename(const std::string& filePath,const std::string& outputFileDir);
		std::string m_OutPutDir;
		Log::LogSystem* m_LogObj;
	};
}
