#pragma once
#include "ImageProcessingView.h"
#include "ImageProcessingModel.h"
#include "FileOperations.h"
#include"LogSystem.h"


namespace Controller
{
    class IController
    {
    public:
        IController() = default;
        virtual ~IController() = default;

        virtual bool StartApplication() =0;
        virtual void PrintStartMessage() = 0;
        virtual void PrintFinalMessage() = 0;
        virtual void QuitApplication() = 0;
    };

    enum UserInputType {
        ApplyBlurfilterToTGAImage = 1, QuitApplication
    };

	class ImageProcessingController:public IController
	{
    public:
        ImageProcessingController(View::ImageProcessingView* ui, Model::ImageProcessingModel* model, Log::LogSystem* logobj)
            :m_pUI(ui), m_pModel(model), m_LogObj(logobj), m_FileOper(m_LogObj)
        {
        }

        bool StartApplication() override;

    private:
        void PrintStartMessage()override;
        void PrintFinalMessage()override;
        void QuitApplication()override;

        void ApplyBlurfilterTGAImage();
        void ProcessTGAImage(std::string_view inputFileName, std::string_view outputFileDir, float blurFactor);
        View::ImageProcessingView* m_pUI;
        Model::ImageProcessingModel* m_pModel;
        Log::LogSystem* m_LogObj;
        FileOperations::FileOperations m_FileOper;
	};
}


