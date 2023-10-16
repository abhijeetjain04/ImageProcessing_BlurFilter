#include "ImageProcessingController.h"
#include <optional>
#include <string>
#include <string_view>
#include <sstream>
#include <fstream>


bool Controller::ImageProcessingController::StartApplication()
{
    bool quit = false;
    PrintStartMessage();
    int UserInput;
    m_pUI->GetInputInteger(UserInput);

    switch (UserInput)
    {
    case UserInputType::BlurTGAImage:
        ProcessTGAImage();
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

void Controller::ImageProcessingController::ProcessTGAImage()
{
    std::string inputFilePath, outputFileDir;
    float blurFactor = 0.0;
    bool validInput = false;
    
    m_pUI->PrintOnScreen("Please enter the full path of the TGA file");
    m_pUI->GetInputString(inputFilePath);

    while (!m_FileOper.IsValidFilePath(inputFilePath) || !m_FileOper.IsTGAFile(inputFilePath))
    {
        m_pUI->PrintOnScreen("Invalid input.Please enter the correct path again");
        m_pUI->GetInputString(inputFilePath);
    }

    while (!validInput)
    {
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

    m_pUI->PrintOnScreen("Please enter the full path of destination folder");
    m_pUI->GetInputString(outputFileDir);

    while (!m_FileOper.IsValidFolderPath(outputFileDir))
    {
        m_pUI->PrintOnScreen("Invalid input.Please enter the correct path again");
        m_pUI->GetInputString(outputFileDir);
    }

    BlurTGAImage(inputFilePath, outputFileDir, blurFactor);
}

void Controller::ImageProcessingController::BlurTGAImage(std::string_view inputFileName, std::string_view outputFileDir, float blurFactor)
{
    FileOperations::TGAFileOperation tgaFileOper;
    FileOperations::TGAHeader tgaHeader;
    std::string outputFileName;
    std::vector<uint8_t> image;

    /*
    std::ifstream file(inputFileName.data(), std::ios::binary);
    if (!file.is_open()) {
        std::cout<<  "Failed to open file: ";
    }

    auto s = sizeof(FileOperations::TGAHeader);
    file.read(reinterpret_cast<char*>(&tgaHeader), sizeof(FileOperations::TGAHeader));

    if (tgaHeader.image_type != 2) {
       std::cout<<  "Unsupported TGA image type: ";
    }

    image.resize(tgaHeader.width * tgaHeader.height * (tgaHeader.pixel_depth / 8));
    file.read(reinterpret_cast<char*>(image.data()), image.size());
    */

    auto [error, ReadOperaSuccess] = tgaFileOper.ReadTGAFile(inputFileName, image, tgaHeader);
    if (!ReadOperaSuccess && error.has_value())
    {
        m_pUI->PrintOnScreen(error.value());
        return;
    }
    m_pModel->ApplyBlur(image, tgaHeader.width, tgaHeader.height, tgaHeader.pixel_depth, blurFactor);

    auto [outerror, WriteOperaSuccess] = tgaFileOper.WriteTGAFile(inputFileName, outputFileDir, image, tgaHeader, outputFileName);
    if (!WriteOperaSuccess && outerror.has_value())
    {
        m_pUI->PrintOnScreen(outerror.value());
        return;
    }

    m_pUI->PrintOnScreen("Your processed is image at " + outputFileName);
   /* std::string outputDir, outputFileName, output;
    m_FileOper.GetCompleteFilename(inputFileName.data(), outputFileName);
    m_FileOper.GetDirectoryPath(inputFileName.data(), outputDir);
    output = outputDir + "/Blur_" + outputFileName;
    std::ofstream outfile(output, std::ios::binary);
    if (!outfile) {
        std::cout << "Failed to create file: ";
    }

    outfile.write(reinterpret_cast<const char*>(&tgaHeader), sizeof(FileOperations::TGAHeader));
    outfile.write(reinterpret_cast<const char*>(image.data()), image.size());*/
}
