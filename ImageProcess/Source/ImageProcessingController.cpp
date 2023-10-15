#include "ImageProcessingController.h"
#include <optional>
#include <string>
#include <sstream>

bool Controller::ImageProcessingController::StartApplication()
{
    bool quit = false;
    PrintStartMessage();
    int UserInput;
    m_pUI->GetInputInteger(UserInput);

    switch (UserInput)
    {
    case UserInputType::BlurTGAImage:
        BlurTGAImage();
        break;
 
    case UserInputType::QuitApplication:
        QuitApplication();
        quit = true;
        break;

    default:
        m_pUI->PrintOnScreen("Invalid Option Selected");
        break;
    }

    PrintFinalMessage();
    return quit;
}

void Controller::ImageProcessingController::PrintStartMessage()
{
    m_pUI->ClearScreen();
    m_pUI->PrintOnScreen("Please select an option:");
    m_pUI->PrintOnScreen("1. Blur TGA Image");
    m_pUI->PrintOnScreen("2. Quit");
}

void Controller::ImageProcessingController::PrintFinalMessage()
{
    m_pUI->PrintOnScreen("Press ENTER to continue.....");
    m_pUI->WaitForUserInput();
}

void Controller::ImageProcessingController::QuitApplication()
{
    m_pUI->PrintOnScreen("Quitting!");
    exit(3);
}

void Controller::ImageProcessingController::BlurTGAImage()
{
    std::string inputFilePath, errorMessage;
    m_pUI->PrintOnScreen("Please enter the full path of the TGA file");
    m_pUI->GetInputString(inputFilePath);

    while (!m_FileOper.IsValidFilePath(inputFilePath, errorMessage))
    {
        m_pUI->PrintOnScreen(errorMessage);
        m_pUI->GetInputString(inputFilePath);
    }

    while (!m_FileOper.IsTGAFile(inputFilePath, errorMessage))
    {
        m_pUI->PrintOnScreen(errorMessage);
        m_pUI->GetInputString(inputFilePath);
    }

    float blurFactor;
    bool validInput = false;

    while (!validInput) {
        std::string userInput;

        m_pUI->PrintOnScreen("Please enter a float between 0.0 and 1.0");
        m_pUI->GetInputString(userInput);

        // Create a stringstream to attempt conversion
        std::istringstream input_stream(userInput);

        // Try to extract a float from the stringstream
        if (input_stream >> blurFactor) {
            // Check if the float is within the desired range
            if (blurFactor >= 0.0 && blurFactor <= 1.0) {
                validInput = true;
            }
            else {
                m_pUI->PrintOnScreen("Invalid input. Please enter a valid float between 0.0 and 1.0.");
            }
        }
        else {
            m_pUI->PrintOnScreen("Invalid input.");
        }

    }
    //processTGAImage(inputFileName, outputFileName, blurFactor)
    
}
