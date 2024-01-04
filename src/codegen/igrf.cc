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
    file.close();
    return lines;

}


std::vector<int> listIGRFModels(std::vector<std::string> lines) {

    std::vector<int> out;
    std::vector<std::string> names = splitByWhitespace(lines[3]);

    int i;
    for (i=3;i<names.size()-1;i++) {
        out.push_back(std::stoi(names[i]));
    }

    /* this bit assumes the last column is formatted like "2020-25" */
    std::vector<std::string> parts = splitByCharacter(names[names.size()-1],'-');
    out.push_back(100*(std::stoi(parts[0])/100) + std::stoi(parts[1]));

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
        model.n.push_back(std::stoi(table[1][i]));
        model.m.push_back(std::stoi(table[2][i]));
        model.v.push_back(std::stod(table[modelInd+3][i])); 
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

    /* convert last model from a secular variation to a prediction*/
    for (int i;i<nRows;i++) {
        out[nModels-1].v[i] = out[nModels-2].v[i] + 5*out[nModels-1].v[i];
    }

    return out;

}

std::string modelLine(char gh, int n, int m, double v) {

    std::ostringstream out;
    out << gh << " ";
    out << std::setw(4) << n << " ";
    out << std::setw(4) << m << " ";
    out << std::setw(14) << std::setprecision(6) << std::fixed << v;
    out << std::endl;

    return out.str();
}


void saveIGRFModel(std::filesystem::path dataPath, igrfModel model) {

    int n = model.gh.size();

    std::filesystem::path fileName = dataPath;
    fileName /= "coeffs";
    fileName /= "earth";
    fileName /= model.name + ".dat";

    
    std::cout << "\t" << fileName << std::endl;

    std::ofstream file(fileName);
    
    for (int i=0;i<n;i++) {
        file << modelLine(model.gh[i],model.n[i],model.m[i],model.v[i]);
    }
    file.close();

}


void saveIGRFModels(std::filesystem::path dataPath) {

    std::vector<igrfModel> models = readIGRF(dataPath);

    std::cout << "Parsing IGRF models..." << std::endl;
    std::cout << "Found " << models.size() << " IGRF models."<< std::endl;
    std::cout << "Saving IGRF coefficients:" << std::endl;

    for (auto &model : models) {
        saveIGRFModel(dataPath,model);
    }
} 