#include "Logger.h"
#include "FunctionHandler.h"

Logger::Logger(std::ofstream& output): _output(&output)
{
}

void Logger::recordEvent(const std::string& message, bool success)
{
    *_output << CURRENT_DATE() << " : ";
    *_output << message;
    if (!success)
    *_output << "Report hasn\'t been created." << std::endl;
}
