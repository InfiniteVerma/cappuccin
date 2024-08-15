#ifndef CAPP_LOGGER
#define CAPP_LOGGER 

#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>

#define LOG() Logger::getInstance()

#define LOG(msg) Logger::getInstance() + msg + Logger::getInstance()::Log()

class Logger {

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    template <typename T>
    Logger& operator<<(const T& data) {
        logMessageStream << data;
        return *this;
    }

    void Log() {
        if(logFile.is_open()){
            // get time
            std::time_t now = std::time(nullptr);
            char timestamp[20];
            std::strftime(timestamp, sizeof(timestamp),  "%Y-%m-%d %H:%M:%S", std::localtime(&now)); 

            // Write the log message
            logFile << "[" << timestamp << "] " << logMessageStream.str() << std::endl;
        } else {
            std::cout << "Log file not open!\n";
        }

        // clear
        logMessageStream.str("");
        logMessageStream.clear();
    }

private:

    Logger();
    ~Logger();

    std::ofstream logFile;
    std::stringstream logMessageStream;
};

#endif // !CAPP_LOGGER
