#include "ImageProcessingController.h"

int main(int, const char* [])
{
	Model::ImageProcessingModel model;
	View::ImageProcessingView ui;

	//Create controller object 
	Controller::ImageProcessingController controller(&ui, &model);

	// Run the application using start application function 
	while (controller.StartApplication() == false)
	{

	}

	return 0;
}
