#pragma once
#include <string>
#include <vector>
#include <ctime>
class FunctionHandler
{
public:
    std::string getFunctionResult(const std::string& input_name);
    bool is_functionRegistered(const std::string& input_name);
    void registerFunction(const std::string& name, std::string(*function)());
private:
    struct Function {
        std::string name;
        std::string(*function)();
    };
    std::vector<Function> _funcList;
};

std::string CURRENT_DATE();