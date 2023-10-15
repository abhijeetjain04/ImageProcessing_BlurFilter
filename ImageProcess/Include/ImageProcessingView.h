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

		//virtual void PrintOnScreen(const std::string& str, bool WantNewLine) = 0;
		virtual void PrintOnScreen(std::string_view str) = 0;
		virtual void GetInputString(std::string& str) = 0;
	};

	//UI implementation of console application    
	class ImageProcessingView : public IImageProcessingView
	{
	public:
		ImageProcessingView() = default;
		~ImageProcessingView() = default;

		//void PrintOnScreen(const std::string& str, bool WantNewLine) override;
		void PrintOnScreen(std::string_view str)override;
		void WaitForUserInput();
		void ClearScreen();
		void GetInputString(std::string& str)override;
		void GetInputInteger(int& inputInt);
	};
};




