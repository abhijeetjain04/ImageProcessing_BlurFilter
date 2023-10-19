#include "ImageProcessingController.h"
#include <optional>
#include <sstream>

bool Controller::ImageProcessingController::StartApplication()
{
    bool quit = false;
    PrintOptions();
    int UserInput;
    m_pUI->GetInputInteger(UserInput);

    switch (UserInput)
    {
    case UserInputType::ApplyBlurfilterToTGAImage:
        ApplyBlurfilterTGAImage();
        break;
 
    case UserInputType::QuitApplication:
        QuitApplication();
        quit = true;
        break;

    default:
        m_pUI->PrintOnScreen("Invalid Option Selected");
        break;
    }

    if (!quit)
    {
        PrintFinalMessage();
    }
    return quit;
}

void Controller::ImageProcessingController::PrintStartMessage()
{
    // Prints start message on the application start 
    m_pUI->ClearScreen();
    m_pUI->PrintOnScreen("************************************************************************");
    m_pUI->PrintOnScreen("****************** Application to apply BLUR FILTER ********************");
    m_pUI->PrintOnScreen("************************************************************************");
    m_pUI->PrintOnScreen("#### 24 and 32 bit uncompressed true-color TGA images are supported ####");
    m_pUI->PrintEmptyLine();
}

void Controller::ImageProcessingController::PrintOptions()
{
    // Prints options  
    m_pUI->PrintOnScreen("Choose options (1) to start blur operations on image  or (2) to exit");
    m_pUI->PrintOnScreen("(1)-> Apply blur filter to TGA image");
    m_pUI->PrintOnScreen("(2)-> Quit application");
    m_pUI->PrintEmptyLine();
}

void Controller::ImageProcessingController::PrintFinalMessage()
{
    m_pUI->PrintOnScreen("Press ENTER to continue.....");
    m_pUI->WaitForUserInput();
    m_pUI->ClearScreen();
}

void Controller::ImageProcessingController::QuitApplication()
{
    m_pUI->PrintOnScreen("Quitting.....");
}

void Controller::ImageProcessingController::ApplyBlurfilterTGAImage()
{
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Apply Blur filter fuction selected.");

    // Take file path from user
    std::string InputFilePath, OutputFileDirectory;
    float BlurFactor = 0.0;
    bool ValidInput = false;
    
    m_pUI->PrintOnScreen("--> Please enter the full path of the TGA file.");
    m_pUI->GetFormattedFilePath(InputFilePath);
    //Validate the file path
    while (!m_FileOper.IsValidFilePath(InputFilePath) || !m_FileOper.IsTGAFile(InputFilePath))
    {
        m_pUI->PrintOnScreen("[ERROR]-> Invalid input.Please enter the correct path again.");
        m_pUI->GetFormattedFilePath(InputFilePath);
    }
    m_pUI->PrintEmptyLine();

    //Read the TGA file and return error if unsupported file format is given
    auto [ReadError, ReadOperaSuccess] =
        m_TGAFileOper.ReadTGAFile(InputFilePath, m_OriginalTGAImage, m_TGAHeader);
    if (!ReadOperaSuccess && ReadError.has_value())
    {
        m_LogObj->LogMessage(Log::LogLevel::ERROR, "Error occurred while reading TGA file");
        m_pUI->PrintOnScreen(ReadError.value());
        return;
    }

    //Take blur factor from user
    m_pUI->PrintOnScreen("--> Please enter a value between 0.0 and 1.0.");
    m_pUI->PrintOnScreen("(0 being no blur and 1 being blurred beyond recognition)");
    while (!ValidInput)
    {
        std::string userInput;
        m_pUI->GetFormattedFilePath(userInput);
        // Create a stringstream to attempt conversion
        std::istringstream input_stream(userInput);

        // Try to extract a float from the stringstream
        if (input_stream >> BlurFactor) {
            // Check if the float is within the desired range
            if (BlurFactor >= 0.0 && BlurFactor <= 1.0) {
                ValidInput = true;
            }
            else {
                m_pUI->PrintOnScreen("[ERROR]-> Invalid input.");
            }
        }
        else {
            m_pUI->PrintOnScreen("[ERROR]-> Please enter valid input.");
        }

    }
    m_pUI->PrintEmptyLine();

    //Take destination folder path from user
    m_pUI->PrintOnScreen("-> Please enter the full path of destination folder.");
    m_pUI->GetFormattedFilePath(OutputFileDirectory);
    m_FileOper.SanitizePath(OutputFileDirectory);
    while (!m_FileOper.IsValidFolderPath(OutputFileDirectory))
    {
        m_pUI->PrintOnScreen("[ERROR]-> Invalid input.Please enter the correct path again.");
        m_pUI->GetFormattedFilePath(OutputFileDirectory);
    }

    m_pUI->PrintEmptyLine();

    //Give all the information for processing 
    ProcessTGAImage(InputFilePath, OutputFileDirectory, BlurFactor);
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Successfully applied Blur filter.");
}

void Controller::ImageProcessingController::ProcessTGAImage(std::string_view inputFileName, std::string_view outputFileDir, float blurFactor)
{
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Started TGA image processing");

    std::string OutputFileName;

    //Give the image and blur factor to model 
    m_pModel->ApplyBoxBlurfilter(m_OriginalTGAImage, m_TGAHeader.width, m_TGAHeader.height, m_TGAHeader.pixel_depth, blurFactor);
   
    //Write blurred TGA image in the given folder path
    auto [WriteError, WriteOperaSuccess] = 
        m_TGAFileOper.WriteTGAFile(inputFileName, outputFileDir,m_OriginalTGAImage, m_TGAHeader, OutputFileName);
    if (!WriteOperaSuccess && WriteError.has_value())
    {
        m_LogObj->LogMessage(Log::LogLevel::ERROR, "Error occurred while writing TGA file");
        m_pUI->PrintOnScreen(WriteError.value());
        return;
    }


    m_pUI->PrintOnScreen("[OUTPUT]-> The blurred image has been successfully generated at: " + OutputFileName);
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Ended TGA image processing");
}
