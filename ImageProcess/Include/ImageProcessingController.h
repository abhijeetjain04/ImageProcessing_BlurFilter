#pragma once
#include "ImageProcessingView.h"
#include "ImageProcessingModel.h"
#include "FileOperations.h"
#include"LogSystem.h"


namespace Controller
{

    enum UserInputType {
        ApplyBlurfilterToTGAImage = 1, QuitApplication
    };

	class ImageProcessingController
	{
    public:
        ImageProcessingController(View::ImageProcessingView* ui, Model::ImageProcessingModel* model, Log::LogSystem* logobj)
            :m_pUI(ui), m_pModel(model), m_LogObj(logobj), m_FileOper(m_LogObj), m_TGAFileOper(m_LogObj) {}

        bool StartApplication();
        void PrintStartMessage();

    private:
        void PrintOptions();
        void PrintFinalMessage();
        void QuitApplication();

        void ApplyBlurfilterTGAImage();
        void ProcessTGAImage(std::string_view inputFileName, std::string_view outputFileDir, float blurFactor);
        View::ImageProcessingView* m_pUI;
        Model::ImageProcessingModel* m_pModel;
        Log::LogSystem* m_LogObj;
        FileOperations::FileOperations m_FileOper;
        FileOperations::TGAFileOperation m_TGAFileOper;
        FileOperations::TGAHeader m_TGAHeader;
        std::vector<uint8_t> m_OriginalTGAImage;
	};
}


