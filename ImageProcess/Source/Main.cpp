#include "ImageProcessingController.h"

int main(int, const char* [])
{
	Model::ImageProcessingModel Model;
	View::ImageProcessingView UI;

	//Create controller object 
	Controller::ImageProcessingController controller(&UI, &Model);

	// Run the application using start application function 
	while (controller.StartApplication() == false)
	{

	}

	return 0;
}
