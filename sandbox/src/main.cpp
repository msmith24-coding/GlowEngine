#include <GlowEngine/utils/Logger.h>
#include <vector>
#include <sstream>

int main(void)
{
    GlowEngine::Logger::get();

    GlowEngine::Logger::logInfo("Sandbox", "This is a test.");
    for(unsigned int i = 0; i < 100; ++i) {
        std::stringstream ss;
        ss << "Testing #" << i;
        GlowEngine::Logger::logInfo("Sandbox", ss.str());
    }

    std::vector<std::string> details;
    details.push_back("Yes, it failed.");
    GlowEngine::Logger::logFatal("Sandbox", "This is a crash", details);

    return 0;
}
