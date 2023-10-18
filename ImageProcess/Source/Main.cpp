#include "ImageProcessingController.h"
#include "LogSystem.h"

int main(int, const char* [])
{
	View::ImageProcessingView UI;
	Log::LogSystem LogObj(&UI,"App.log");
	Model::ImageProcessingModel Model(&LogObj);

	//Create controller object 
	Controller::ImageProcessingController Controller(&UI, &Model, &LogObj);
	Controller.PrintStartMessage();
	// Run the application using start application function 
	while (Controller.StartApplication() == false)
	{
	}

	return 0;
}
