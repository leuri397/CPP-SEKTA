#include "FunctionHandler.h"

std::string FunctionHandler::getFunctionResult(const std::string& input_name)
{
    for (int i = 0; i < _funcList.size(); i++)
    {
        if (_funcList[i].name == input_name)
            return _funcList[i].function();
    }
    throw std::exception("function isn\'t found");
}

bool FunctionHandler::is_functionRegistered(const std::string& input_name)
{
    for (int i = 0; i < _funcList.size(); i++)
    {
        if (_funcList[i].name == input_name)
            return true;
    }
    return false;
}

void FunctionHandler::registerFunction(const std::string& name, std::string(*function)())
{
    _funcList.push_back({ name, function});
}

std::string CURRENT_DATE() {
    std::string result;
    char buffer[20];
    time_t time_v;
    time_t* time_val = &time_v;
    time(time_val);
    tm date_time;
    tm* value = &date_time;
    localtime_s(value, time_val);
    _itoa_s(value->tm_mday, buffer, 10);
    result += buffer;
    result += "\\";
    _itoa_s(value->tm_mon + 1, buffer, 10);
    result += buffer;
    result += "\\";
    _itoa_s(value->tm_year + 1900, buffer, 10);
    result += buffer;
    result += " ";
    _itoa_s(value->tm_hour, buffer, 10);
    if (strlen(buffer) == 1)
        result += "0";
    result += buffer;
    result += ":";
    _itoa_s(value->tm_min, buffer, 10);
    if (strlen(buffer) == 1)
        result += "0";
    result += buffer;
    result += ":";
    _itoa_s(value->tm_sec, buffer, 10);
    if (strlen(buffer) == 1)
        result += "0";
    result += buffer;
    return result;
}