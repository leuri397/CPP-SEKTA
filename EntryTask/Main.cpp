#include <iostream>
#include <fstream>
#include <vector>
#include "ReportLine.h"
#include "FunctionHandler.h"
#include "XMLParser.h"
#include "Logger.h"

const std::string& getValueFromList(const std::vector<Parameter>& list, const std::string& parameter);

int main(int argc, char* argv[])
{
    std::string inputTemplate, inputXML, outputTXT;
    bool console = false;
    if (argc < 4)
    {
        std::cerr << "Wrong amount of arguments\n";
        return -1;
    }
    else
    {
        inputTemplate = argv[1];
        inputXML = argv[2];
        if (argv[3] == "-c")
            console = true;
        else
        {
            console = false;
            outputTXT = argv[4];
        }
    }
    std::ifstream input_parameters, input_template;
    std::ofstream log;
    input_parameters.open(inputXML, std::ios_base::in);
    input_template.open(inputTemplate, std::ios_base::in);
    log.open("current_log.txt", std::ios_base::out);
    XMLParser parser(input_parameters);
    ReportLine line;
    Logger newLogger(log);
    FunctionHandler func;
    func.registerFunction("current_date", CURRENT_DATE);
    std::string reportText;
    try {
        std::vector<Parameter> allXMLParameters(parser.getParameters());

        for (int i = 0; i < allXMLParameters.size(); i++)
        {
            if (func.is_functionRegistered(allXMLParameters[i].name))
            {
                newLogger.recordEvent("Function get in XML parameters. ", false);
                return -1;
            }
        }
        char buffer[256];
        while (!input_template.eof())
        {
            input_template.getline(buffer, 256);
            reportText += buffer;
            reportText += "\n";
        }
        line.setLine(reportText);
        std::vector<std::string> neededParams(line.getParamNameList());
        for (int i = 0; i < neededParams.size(); i++)
        {
            if (func.is_functionRegistered(neededParams[i]))
            {
                line.setParam(neededParams[i], func.getFunctionResult(neededParams[i]));
                continue;
            }
            line.setParam(neededParams[i], getValueFromList(allXMLParameters, neededParams[i]));
        }
    }
    catch (const std::exception& err)
    {
        newLogger.recordEvent(err.what(), false);
        return -1;
    }
    if (console)
    {
        std::cout << line.getFinishedLine();
    }
    else
    {
        std::ofstream output;
        output.open(outputTXT, std::ios_base::out);
        output << line.getFinishedLine();
    }
    newLogger.recordEvent("Report successfully created. ", true);
}

const std::string& getValueFromList(const std::vector<Parameter>& list, const std::string& parameter)
{
    static std::string emptyString;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].name == parameter)
            return list[i].value;
    }
    return emptyString;
}
