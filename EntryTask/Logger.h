#pragma once
#include <fstream>
class Logger
{
public:
    Logger(std::ofstream& output);
    void recordEvent(const std::string& message, bool success);
private:
    std::ofstream* _output;
};

