#include "logger.h"
#include "iostream"

#define LOG_FILE_NAME "cappuccinlog"

Logger::Logger()
{
    logFile.open(LOG_FILE_NAME, std::ios::out | std::ios::app);

    if(!logFile.is_open()){
        std::cout << "Err in opening file TODO show error no" << std::endl;
    }

    logFile << "Hello";
}

Logger::~Logger()
{
    if(logFile.is_open())
        logFile.close();
}

void
Logger::Log(const std::string& message)
{
    if(logFile.is_open()){
        logFile << message << std::endl;
    }
}
