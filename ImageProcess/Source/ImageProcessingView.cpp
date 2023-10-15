#include "ImageProcessingView.h"


void View::ImageProcessingView::PrintOnScreen(std::string_view str)
{
	std::cout << str << std::endl;
}

void View::ImageProcessingView::WaitForUserInput()
{
	std::string temp;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, temp);
}

void View::ImageProcessingView::ClearScreen()
{
	for (int i = 0; i < 80; ++i) std::cout << std::endl;
}

void View::ImageProcessingView::GetInputString(std::string& str)
{
	std::getline(std::cin >> std::ws, str);
}

void View::ImageProcessingView::GetInputInteger(int& inputInt)
{
	std::cin >> inputInt;
}