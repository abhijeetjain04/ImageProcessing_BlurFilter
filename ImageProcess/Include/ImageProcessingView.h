#pragma once

#include <iostream>
#include <string>
#include <string_view>

namespace View
{
	class IView
	{
	public:
		IView() = default;
		virtual ~IView() = default;

		virtual void PrintOnScreen(std::string_view str) = 0;
		virtual void GetFormattedFilePath(std::string& str) = 0;
	};

	//UI implementation of console application    
	class ImageProcessingView : public IView
	{
	public:
		void PrintOnScreen(std::string_view str)override;
		void GetFormattedFilePath(std::string& str)override;
		void ClearScreen();
		void PrintEmptyLine();
		void WaitForUserInput();
		void GetInputInteger(int& inputInt);
	};
};




