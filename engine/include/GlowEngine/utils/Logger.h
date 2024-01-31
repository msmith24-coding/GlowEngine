#ifndef GLOWENGINE_LOGGER_H_
#define GLOWENGINE_LOGGER_H_

#include <string>
#include <vector>

namespace GlowEngine 
{

    enum class LogLevel
    {
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    // Singleton
    class Logger 
    {
        private: 
            static inline Logger* instance = nullptr;
        public: // Singleton Management Static Methods.
            static Logger& get();
        public: // Singleton Logging Static Methods.  
            static void logInfo(const std::string& location, const std::string& message);
            static void logWarn(const std::string& location, const std::string& message);
            static void logError(const std::string& location, const std::string& message, std::vector<std::string>& details);
            static void logFatal(const std::string& location, const std::string& message, std::vector<std::string>& details);
        private: // Member Utility Variables.
            std::string logDirectoryName = "log/";
            unsigned int maxLogsCached = 255;
            std::vector<std::string> logCache;
        private: // Member Utility Methods.
            std::string getFormattedLevel(LogLevel level) const;
            std::string getFormattedTime() const;
            std::string getFormattedPrefix(LogLevel level, const std::string& location) const;

            void addLogToCacheLog(const std::string& log); 
            void createCrashLog();
    };
}

#endif
