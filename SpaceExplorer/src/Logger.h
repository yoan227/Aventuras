//
// Created by zunig on 6/11/2026.
//

#ifndef AVENTURAS_LOGGER_H
#define AVENTURAS_LOGGER_H


#include <string>
#include <vector>
#include <fstream>

// Records all simulation events to memory and to a log file
class Logger {
public:
    explicit Logger(const std::string& logFilePath);
    ~Logger();

    void log(const std::string& message);
    void writeReport(const std::string& reportFilePath,
                     const std::string& summary) const;

private:
    std::ofstream logFile;
    std::vector<std::string> entries;

    std::string timestamp(int step) const;
    int step;
};

#endif //AVENTURAS_LOGGER_H
