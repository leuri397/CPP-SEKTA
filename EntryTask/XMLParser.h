#pragma once
#include <iostream>
#include <fstream>
#include <vector>
struct Parameter {
    std::string name;
    std::string value;
};
class XMLParser
{
public:
    XMLParser(std::ifstream&);
    const std::vector<Parameter>& getParameters();
private:
    std::ifstream* _input;
};

