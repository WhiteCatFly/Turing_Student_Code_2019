#include "Logger.hpp"

#include <chrono>
#include <iomanip>
#include <sstream>

namespace cowr {

std::string Logger::defaultFormatter(bool useColor, int level, std::string msg)
{
    std::stringstream buffer;

    buffer << "[";

    if (useColor) {
        switch (level) {
        case DEBUG:
        case INFO:
            break;

        case WARNING:
            buffer << TermUtil::setForeGroundColor(TermUtil::YELLOW);
            break;

        case ERROR:
        case CRITICAL:
            buffer << TermUtil::setForeGroundColor(TermUtil::RED);
            break;

        default:
            break;
        }
    }

    switch (level) {
    case DEBUG:
        buffer << " DEBUG    ";
        break;
    case INFO:
        buffer << " INFO     ";
        break;
    case WARNING:
        buffer << " WARNING  ";
        break;
    case ERROR:
        buffer << " ERROR    ";
        break;
    case CRITICAL:
        buffer << " CRITICAL ";
        break;

    default:
        buffer << " UNKNOWN  ";
        break;
    }

    if (useColor)
        buffer << TermUtil::resetAttr();

    buffer << "] (";

    auto now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    buffer << std::put_time(std::localtime(&now_time), "%F %T");

    buffer << "): " << msg;

    return buffer.str();
}
}