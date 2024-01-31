#include <GlowEngine/utils/Logger.h>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <filesystem>

//
// Singleton Management Static Methods:
//

GlowEngine::Logger& GlowEngine::Logger::get()
{
    // Checks if the Logger instance has not been created.
    if(GlowEngine::Logger::instance == nullptr) {
        // Create a new instance of the Logger.
        GlowEngine::Logger::instance = new GlowEngine::Logger();
    }
    // Return a reference to the Logger instance.
    return *GlowEngine::Logger::instance;
}

//
// Singleton Logger Static Methods:
//

void GlowEngine::Logger::logInfo(const std::string& location, const std::string& message)
{
    std::stringstream ss;
    ss << GlowEngine::Logger::get().getFormattedPrefix(GlowEngine::LogLevel::INFO, location) << message << std::endl;  
    
    std::cout << ss.str();

    GlowEngine::Logger::get().addLogToCacheLog(ss.str()); 
}

void GlowEngine::Logger::logWarn(const std::string &location, const std::string &message)
{
    std::stringstream ss;
    ss << GlowEngine::Logger::get().getFormattedPrefix(GlowEngine::LogLevel::WARN, location) << message << std::endl;

    std::cout << ss.str();

    GlowEngine::Logger::get().addLogToCacheLog(ss.str());

}

void GlowEngine::Logger::logError(const std::string &location, const std::string &message, std::vector<std::string> &details)
{
    std::stringstream ss;
    ss << GlowEngine::Logger::get().getFormattedPrefix(GlowEngine::LogLevel::ERROR, location) << message << std::endl;
    ss << "  " << "Error Details:" << std::endl;
    for(unsigned int i = 0; i < details.size(); ++i) {
        ss << "      " << details.at(i) << std::endl;
    }

    std::cerr << ss.str(); 
    GlowEngine::Logger::get().addLogToCacheLog(ss.str());
}

void GlowEngine::Logger::logFatal(const std::string &location, const std::string &message, std::vector<std::string> &details)
{
    std::stringstream ss;
    ss << GlowEngine::Logger::get().getFormattedPrefix(GlowEngine::LogLevel::FATAL, location) << message << std::endl;
    ss << "  " << "Crash Details:" << std::endl;
    for(unsigned int i = 0; i < details.size(); ++i) {
        ss << "      " << details.at(i) << std::endl;
    }

    std::cerr << ss.str(); 
    GlowEngine::Logger::get().addLogToCacheLog(ss.str());
    
    GlowEngine::Logger::get().createCrashLog();
}

// 
// Member Utility Methods:
//

std::string GlowEngine::Logger::getFormattedLevel(GlowEngine::LogLevel level) const
{
    switch (level) 
    {
        case GlowEngine::LogLevel::INFO: return "- INFO -";
        case GlowEngine::LogLevel::WARN: return "- WARN -";
        case GlowEngine::LogLevel::ERROR: return "- ERROR -";
        case GlowEngine::LogLevel::FATAL: return "- FATAL -";
        default: return "- UNKNOWN -";
    }
}

std::string GlowEngine::Logger::getFormattedTime() const
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::string strTime = std::ctime(&time);
    strTime = strTime.substr(0, strTime.length() - 1);

    std::stringstream ss;

    ss << strTime;

    return ss.str();
}

std::string GlowEngine::Logger::getFormattedPrefix(GlowEngine::LogLevel level, const std::string& location) const
{
    std::stringstream ss;
    ss << "[" << this->getFormattedTime() << "]" << " " << this->getFormattedLevel(level) << " " << location << ": ";
    return ss.str();
}

void GlowEngine::Logger::addLogToCacheLog(const std::string& log)
{
    if(this->logCache.size() > this->maxLogsCached) {
        this->logCache.erase(this->logCache.begin(), this->logCache.begin());
    }
    this->logCache.push_back(log);
}

void GlowEngine::Logger::createCrashLog()
{
    std::string applicationName = "GlowEngine";
    std::string applicationVersion = "v0.1.0";
    
    std::stringstream ss;

    ss << applicationName << "_" << applicationVersion << "_CrashLog_" << this->getFormattedTime() << ".log";
    
    std::string crashDirectory = "crash-reports/";
    std::string fileName = ss.str();

    if(!std::filesystem::exists(crashDirectory)) {
        if(!std::filesystem::create_directory(crashDirectory)) {
            
            std::vector<std::string> details;
            details.push_back("Does the directory already exist?");

            GlowEngine::Logger::logError("Logger", "Failed to create a directory.", details);
            exit(1); 
        }
    }
    
    std::string filePath = crashDirectory + fileName;
    std::ofstream outFile(filePath, std::ios::app);

    if(!outFile.is_open()) {
        std::vector<std::string> details;
        details.push_back("Does the crash log exist?");
        
        GlowEngine::Logger::logError("Logger", "Failed to open crash log.", details);
        exit(1);
    }
    
    for(unsigned int i = 0; i < this->logCache.size(); ++i) {
        outFile << this->logCache.at(i);
    } 

    outFile.close();
    exit(1);
}

