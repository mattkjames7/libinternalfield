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

std::vector<std::string> splitByWhitespace(const std::string& str) {
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string word;

    while (iss >> word) {
        result.push_back(word);
    }

    return result;
}

std::vector<int> listIGRFModels(std::vector<std::string> lines) {

    std::vector<std::int> out;
    std::vector<std::string> names = splitByWhitespace(lines[3]);

    int i;
    for (i=3;i<names.size()-1;i++) {
        out.push_back(atoi(names[i]));
    }

    /* this bit assumes the last column is formatted like "2020-25" */
    std::vector<std::string> parts = splitByCharacter(names[names.size()-1],'-');
    out.push_back(100*(atoi(parts[0])/100) + atoi(parts[1]));

    return out;
}

std::vector<std::vector<std::string>> getIGRFTable(std::vector<std::string> lines) {
    
    /* this returns all values contained in the table */
    int nRows, nCols;
    nRows = lines.size() - 4;

    std::vector<std::string> tmp = splitByWhitespace(lines[5]);
    nCols = tmp.size();

    if (splitByWhitespace(lines[lines.size()-1]).size() < nCols) {
        nRows -= 1;
    }

    std::vector<std::vector<std::string>> table(nCols, std::vector<std::string>(nRows));

    for (int i=0;i<nRows;i++) {
        tmp = splitByWhitespace(lines[i+4]);
        for (int j=0;j<nCols;j++) {
            table[j][i] = tmp[j];
        }
    }

    return table;
}

igrfModel fillModel(int modelInd, int nRows, std::vector<int> modelYears,
        std::vector<std::vector<std::string>> table) {
    
    igrfModel model;
    model.name = "igrf" + std::to_string(modelYears[modelInd]);

    for (int i=0;i<nRows;i++) {
        model.gh.push_back(table[0][i].c_str()[0]);
        model.n.push_back(atoi(table[1][i]));
        model.m.push_back(atoi(table[2][i]));
        model.v.push_back(atof(table[modelInd+3][i])); 
    }

    return model;
}

std::vector<igrfModel> readIGRF(std::filesystem::path dataPath) {

    std::vector<std::string> lines = readIGRFFile(dataPath);

    std::vector<int> modelYears = listIGRFModels(lines);

    std::vector<std::vector<std::string>> table = getIGRFTable(lines);

    int nModels = modelYears.size();
    int nRows = table[0].size();

    std::vector<igrfModel> out;
    for (int i=0;i<nModels;i++) {
        out.push_back(fillModel(i,nRows,modelYears,table));
    }

    return out;

}