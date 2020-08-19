#pragma once
#include <string>
#include <vector>
#include <iterator>
#include <unordered_set>
class ReportLine
{
public:
    ReportLine() = default;
    ReportLine(const std::string& input);
    void setLine(const std::string& input);
    void setParam(const std::string& parameter, const std::string& value);
    const std::string& getFinishedLine();
    const std::vector<std::string>& getParamNameList();
private:
    struct ParamInfo {
        std::string name;
        std::string value;
        bool is_mandatory;
        std::vector<size_t> positions;
    };
    std::string _line;
    std::vector<ParamInfo> _paramList;
    void updatePositions(size_t position, std::vector<ParamInfo>& input, size_t length);
};

