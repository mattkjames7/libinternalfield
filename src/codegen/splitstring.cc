#include "splitstring.h"

std::vector<std::string> splitByCharacter(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));
    return result;
}

std::vector<std::string> splitByWhitespace(const std::string& str) {
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string word;

    while (iss >> word) {
        result.push_back(word);
    }

    return result;
}
