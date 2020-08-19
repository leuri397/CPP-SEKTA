#include "ReportLine.h"

ReportLine::ReportLine(const std::string& input)
{
    setLine(input);
}

void ReportLine::setLine(const std::string& input)
{
    std::unordered_set<std::string> usedNames;
    _paramList.clear();
    std::string bufferLine = input;
    ParamInfo parameter;
    size_t openPosition = bufferLine.find_first_of('{');
    size_t closePosition;
    while (openPosition != std::string::npos)
    {
        closePosition = bufferLine.find_first_of('}');
        if ((closePosition == std::string::npos) || (closePosition < openPosition))
            throw std::exception("Error reading report. ");
        parameter.positions.push_back(openPosition);
        parameter.name = bufferLine.substr(openPosition + 1, closePosition - openPosition - 1);
        bufferLine.erase(openPosition, closePosition - openPosition + 1);
        if (parameter.name[0] == '*')
        {
            parameter.is_mandatory = true;
            parameter.name.erase(0, 1);
        }
        else
        {
            parameter.is_mandatory = false;
        }
        if (usedNames.find(parameter.name) == usedNames.end())
        {
            _paramList.push_back(parameter);
            usedNames.insert(parameter.name);
        }
        else
        {
            for (int i = 0; i < _paramList.size(); i++)
            {
                if (_paramList[i].name == parameter.name)
                {
                    _paramList[i].positions.push_back(openPosition);
                    _paramList[i].is_mandatory |= parameter.is_mandatory;
                }
            }
        }
        
        openPosition = bufferLine.find_first_of('{');
        parameter.positions.clear();
    }
    _line = bufferLine;
}

void ReportLine::setParam(const std::string& parameter, const std::string& value)
{
    bool success = false;
    for (int i = 0; i < _paramList.size(); i++)
    {
        if (_paramList[i].name == parameter)
        {
            _paramList[i].value = value;
            success = true;
        }
    }
    if (!success)
        throw std::exception("Unknown parameter. ");
}

const std::string& ReportLine::getFinishedLine()
{
    static std::string outputLine(_line);
    outputLine = _line;
    std::vector<ParamInfo> parameters(_paramList);
    for (int i = 0; i < parameters.size(); i++)
    {
        for (int j = 0; j < parameters[i].positions.size(); j++)
        {
            outputLine.insert(parameters[i].positions[j], parameters[i].value);
            if ((parameters[i].value.empty()) && parameters[i].is_mandatory)
                throw std::exception("Not all mandatory parameters set. ");
            updatePositions(parameters[i].positions[j], parameters, parameters[i].value.size());
        }
    }
    return outputLine;
}

const std::vector<std::string>& ReportLine::getParamNameList()
{
   static std::vector<std::string> output;
    for (int i = 0; i < _paramList.size(); i++)
        output.push_back(_paramList[i].name);
    return output;
}

void ReportLine::updatePositions(size_t position, std::vector<ParamInfo>& input, size_t length)
{
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].positions.size(); j++)
        {
            if (input[i].positions[j] > position)
                input[i].positions[j] += length;
        }
    }
}
