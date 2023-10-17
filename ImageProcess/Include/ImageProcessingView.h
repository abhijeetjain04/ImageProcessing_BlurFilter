#pragma once

#include <iostream>
#include <string>
#include <string_view>

namespace View
{
	class IImageProcessingView
	{
	public:
		IImageProcessingView() = default;
		virtual ~IImageProcessingView() = default;

		virtual void PrintOnScreen(std::string_view str) = 0;
		virtual void FormattedFilePath(std::string& str) = 0;
	};

	//UI implementation of console application    
	class ImageProcessingView : public IImageProcessingView
	{
	public:
		ImageProcessingView() = default;
		~ImageProcessingView() = default;

		void PrintOnScreen(std::string_view str)override;
		void FormattedFilePath(std::string& str)override;
		void PrintEmptyLine();
		void WaitForUserInput();
		void ClearScreen();
		void GetInputInteger(int& inputInt);
	};
};




