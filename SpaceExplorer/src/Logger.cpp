//
// Created by zunig on 6/11/2026.
//

#include "Logger.h"
#include "Logger.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

Logger::Logger(const std::string& logFilePath) : step(0) {
    logFile.open(logFilePath);
    if (!logFile.is_open()) {
        throw std::runtime_error("Could not open log file: " + logFilePath);
    }
    logFile << "=== SPACE EXPLORER - SIMULATION LOG ===" << std::endl;
}

Logger::~Logger() {
    if (logFile.is_open()) logFile.close();
}

void Logger::log(const std::string& message) {
    step++;
    std::string entry = timestamp(step) + " " + message;
    entries.push_back(entry);
    logFile << entry << std::endl;
    std::cout << entry << std::endl;
}

void Logger::writeReport(const std::string& reportFilePath,
                          const std::string& summary) const {
    std::ofstream report(reportFilePath);
    if (!report.is_open()) {
        throw std::runtime_error("Could not open report file: " + reportFilePath);
    }

    report << "========================================" << std::endl;
    report << "   SPACE EXPLORER - FINAL REPORT" << std::endl;
    report << "========================================" << std::endl;
    report << summary << std::endl;
    report << std::endl;
    report << "--- EVENT LOG ---" << std::endl;
    for (const auto& entry : entries) {
        report << entry << std::endl;
    }
    report << "========================================" << std::endl;
    report.close();
}

std::string Logger::timestamp(int s) const {
    std::ostringstream oss;
    oss << "[STEP " << std::setw(3) << std::setfill('0') << s << "]";
    return oss.str();
}