#include "ImageProcessingController.h"
#include <optional>
#include <sstream>

bool Controller::ImageProcessingController::StartApplication()
{
    bool quit = false;
    PrintStartMessage();
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
    m_pUI->ClearScreen();
    m_pUI->PrintOnScreen("Please enter number written in front of option to select the option:");
    m_pUI->PrintOnScreen("(1). Apply blur filter to TGA image");
    m_pUI->PrintOnScreen("(2). Quit application");
}

void Controller::ImageProcessingController::PrintFinalMessage()
{
    m_pUI->PrintOnScreen("Press ENTER to continue.....");
    m_pUI->WaitForUserInput();
}

void Controller::ImageProcessingController::QuitApplication()
{
    m_pUI->PrintOnScreen("Quitting.....");
}

void Controller::ImageProcessingController::ApplyBlurfilterTGAImage()
{
    m_LogObj->LogMessage(Log::LogLevel::INFO, "Blur TGA image fuction selected");

    std::string InputFilePath, OutputFileDirectory;
    float BlurFactor = 0.0;
    bool ValidInput = false;
    
    m_pUI->PrintOnScreen("Please enter the full path of the TGA file");
    m_pUI->FormattedFilePath(InputFilePath);
    while (!m_FileOper.IsValidFilePath(InputFilePath) || !m_FileOper.IsTGAFile(InputFilePath))
    {
        m_pUI->PrintOnScreen("Invalid input.Please enter the correct path again");
        m_pUI->FormattedFilePath(InputFilePath);
    }

    m_pUI->PrintEmptyLine();

    while (!ValidInput)
    {
        std::string userInput;

        m_pUI->PrintOnScreen("Please enter a float between 0.0 and 1.0");
        m_pUI->FormattedFilePath(userInput);

        // Create a stringstream to attempt conversion
        std::istringstream input_stream(userInput);

        // Try to extract a float from the stringstream
        if (input_stream >> BlurFactor) {
            // Check if the float is within the desired range
            if (BlurFactor >= 0.0 && BlurFactor <= 1.0) {
                ValidInput = true;
            }
            else {
                m_pUI->PrintOnScreen("Invalid input. Please enter a valid float between 0.0 and 1.0.");
            }
        }
        else {
            m_pUI->PrintOnScreen("Invalid file format. Please enter a valid float between 0.0 and 1.0.");
        }

    }

    m_pUI->PrintEmptyLine();

    m_pUI->PrintOnScreen("Please enter the full path of destination folder");
    m_pUI->FormattedFilePath(OutputFileDirectory);
    m_FileOper.SanitizePath(OutputFileDirectory);
    while (!m_FileOper.IsValidFolderPath(OutputFileDirectory))
    {
        m_pUI->PrintOnScreen("Invalid input.Please enter the correct path again");
        m_pUI->FormattedFilePath(OutputFileDirectory);
    }

    m_pUI->PrintEmptyLine();

    ProcessTGAImage(InputFilePath, OutputFileDirectory, BlurFactor);
}

void Controller::ImageProcessingController::ProcessTGAImage(std::string_view inputFileName, std::string_view outputFileDir, float blurFactor)
{
    m_LogObj->LogMessage(Log::LogLevel::INFO, "User has entered all the required input.");
    FileOperations::TGAFileOperation TGAFileOper(m_LogObj);
    FileOperations::TGAHeader TGAHeader;
    std::string OutputFileName;
    std::vector<uint8_t> OriginalTGAImage;

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

    auto [ReadError, ReadOperaSuccess] = TGAFileOper.ReadTGAFile(inputFileName, OriginalTGAImage, TGAHeader);
    if (!ReadOperaSuccess && ReadError.has_value())
    {
        m_LogObj->LogMessage(Log::LogLevel::ERROR, "Error occurred while reading TGA file");
        m_pUI->PrintOnScreen(ReadError.value());
        return;
    }
   
    m_pModel->ApplyBoxBlurfilter(OriginalTGAImage, TGAHeader.width, TGAHeader.height, TGAHeader.pixel_depth, blurFactor);
   
    auto [WriteError, WriteOperaSuccess] = TGAFileOper.WriteTGAFile(inputFileName, outputFileDir, OriginalTGAImage, TGAHeader, OutputFileName);
    if (!WriteOperaSuccess && WriteError.has_value())
    {
        m_LogObj->LogMessage(Log::LogLevel::ERROR, "Error occurred while writing TGA file");
        m_pUI->PrintOnScreen(WriteError.value());
        return;
    }

    m_pUI->PrintOnScreen("[OUTPUT]->Your blurred image is at " + OutputFileName);
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
