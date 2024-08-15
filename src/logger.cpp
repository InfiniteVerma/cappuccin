#include "logger.h"
#include "iostream"

#define LOG_FILE_NAME "cappuccinlog"

Logger::Logger() {
    logFile.open("mylog.txt", std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open log file mylog.txt" << std::endl;
    }
}

//Logger::Logger()
//{
//    logFile.open(LOG_FILE_NAME, std::ios::out | std::ios::app);
//
//    if(!logFile.is_open()){
//        std::cout << "Err in opening file TODO show error no" << std::endl;
//    }
//
//    logFile << "Hello";
//    std::cout << "Written hello to file!\n";
//}

Logger::~Logger()
{
    if(logFile.is_open())
        logFile.close();
}
