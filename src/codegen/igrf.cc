#include "igrf.h"

std::vector<std::string> readIGRFFile(std::filesystem::path dataPath) {

    std::filesystem::path igrfFile = dataPath;
    igrfFile /= "igrf/igrf13coeffs.txt";

    std::ifstream file(igrfFile);

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file,line)) {
        lines.push_back(line);
    }

    return lines;

}

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


std::vector<int> listIGRFModels(std::vector<std::string> lines) {

    std::vector<std::int> out;
    std::vector<std::string> names = splitByCharacter(lines[3],' ');

    int i;
    for (i=0;i<names.size()-1;i++) {
        out.push_back(atoi(names[i]));
    }

    /* this bit assumes the last column is formatted like "2020-25" */
    std::vector<std::string> parts = splitByCharacter(names[names.size()-1],'-');
    out.push_back(100*(atoi(parts[0])/100) + atoi(parts[1]));

    return out;
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