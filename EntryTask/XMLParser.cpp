#include "XMLParser.h"

XMLParser::XMLParser(std::ifstream& input): _input(&input)
{
}

const std::vector<Parameter>& XMLParser::getParameters()
{
    static std::vector<Parameter> output;
    Parameter single;
    output.clear();
    std::string rawInput;
    char buffer[100];
    *_input >> rawInput;

    while (!(*_input).eof())
    {
        (*_input).getline(buffer, 100);
        rawInput += buffer;
    }

    while (rawInput.find_first_of("\t") != std::string::npos)
    {
        rawInput.erase(rawInput.find_first_of("\t"), 1);
    }
    if ((rawInput.find("<report>") == std::string::npos) || (rawInput.find("</report>") == std::string::npos))
    {
        throw std::exception("Error reading XML. ");
    }
    rawInput = rawInput.substr(rawInput.find("<report>") + 8, rawInput.find("</report>") - rawInput.find("<report>") - 8);
    while (!rawInput.empty())
    {
        if ((rawInput.find("<") > rawInput.find(">")) || (rawInput.find("<") == std::string::npos) || (rawInput.find(">") == std::string::npos))
            throw std::exception("Error reading XML. ");
        std::string name = rawInput.substr(rawInput.find("<") + 1, rawInput.find(">") - rawInput.find("<") - 1);
        single.name = name;
        if ((rawInput.find("<" + name + ">") > rawInput.find("</" + name + ">")) || (rawInput.find("</" + name + ">") == std::string::npos) || (rawInput.find("<" + name + ">") == std::string::npos))
            throw std::exception("Error reading XML. ");
        std::string value = rawInput.substr(rawInput.find("<" + name + ">") + name.size() + 2, rawInput.find("</" + name + ">") - rawInput.find("<" + name + ">") - name.size() - 2);
        single.value = value;
        rawInput.erase(rawInput.find("<" + name + ">"), value.size() + 2*name.size() + 5);
        output.push_back(single);
    }
    return output;
}

