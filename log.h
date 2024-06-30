#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>

class DailyLogger {
private:
    std::string logDirectory;
    std::string currentLogFile;

    std::string getCurrentLogFileName() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_c);

        std::stringstream ss;
        ss << std::put_time(&now_tm, "%Y-%m-%d"); // 正确使用 put_time
        return ss.str();
    }

public:
    DailyLogger(const std::string& directory) : logDirectory(directory) {
        currentLogFile = logDirectory+getCurrentLogFileName()+".log";
    }

    void log(const std::string& message) {
        std::ofstream logFile(currentLogFile, std::ios::out | std::ios::app); // 追加模式，如果文件不存在则创建
        if (!logFile) {
            std::cerr << "Failed to open log file: " << currentLogFile << std::endl;
            return;
        }
        logFile << message << std::endl;
    }
};
