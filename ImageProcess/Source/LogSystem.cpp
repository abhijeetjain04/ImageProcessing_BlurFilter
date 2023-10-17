#include "LogSystem.h"


Log::LogSystem::LogSystem(View::ImageProcessingView* ui, const std::string& logFileName):m_pUI(ui)
{
    logFile.open(logFileName, std::ios::app);
    if (!logFile.is_open()) {
        m_pUI->PrintOnScreen("[Error]->Failed to open the log file.");
    }
}

Log::LogSystem::~LogSystem()
{
    if (logFile.is_open()) 
    {
        logFile << "---------------------------------------------------- " << std::endl;
        logFile.close();
    }
}

void Log::LogSystem::LogMessage(LogLevel level, const std::string& message)
{
    if (logFile.is_open()) {
        auto timestamp = std::chrono::system_clock::now();
        std::time_t now = std::chrono::system_clock::to_time_t(timestamp);

        char timeBuffer[26];
        ctime_s(timeBuffer, sizeof(timeBuffer), &now);

        logFile << timeBuffer << " " << LogLevelToString(level) << ": " << message << std::endl;
    }
}