#ifndef CAPP_LOGGER
#define CAPP_LOGGER 

#include <string>
#include <fstream>

class Logger {

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void Log(const std::string& message);
private:

    Logger();
    ~Logger();

    std::ofstream logFile;
};

#endif // !CAPP_LOGGER
