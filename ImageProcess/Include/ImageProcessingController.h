#pragma once
#include "ImageProcessingView.h"
#include "ImageProcessingModel.h"
#include "FileOperations.h"

namespace Controller
{
    enum UserInputType {
        BlurTGAImage = 1, QuitApplication
    };

	class ImageProcessingController
	{
    public:
        ImageProcessingController(View::ImageProcessingView* ui, Model::ImageProcessingModel* model) :m_pUI(ui), m_pModel(model) 
        {
        }

        bool StartApplication();

    private:
        void PrintStartMessage();
        void PrintFinalMessage();
        void QuitApplication();

        void ProcessTGAImage();
        void BlurTGAImage(std::string_view inputFileName, std::string_view outputFileDir, float blurFactor);
        View::ImageProcessingView* m_pUI;
        Model::ImageProcessingModel* m_pModel;
        FileOperations::FileOperations m_FileOper;
	};
}


