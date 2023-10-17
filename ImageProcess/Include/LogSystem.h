#pragma once
#include "ImageProcessingView.h"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

namespace Log
{
    // Enum for log levels
    enum class LogLevel
    {
        INFO,
        WARNING,
        ERROR
    };

    class LogSystem
    {
    public:
        LogSystem(View::ImageProcessingView* ui, const std::string& logFileName);
        ~LogSystem();
        void LogMessage(LogLevel level, const std::string& message);
    private:
        // Helper function to convert LogLevel to string
        std::string LogLevelToString(LogLevel level)
        {
            switch (level) {
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            }
            return "UNKNOWN";
        }
        std::ofstream logFile;
        View::ImageProcessingView* m_pUI;
    };

}
