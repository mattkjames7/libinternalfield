#include "savevariable.h"

FileList listAllVariableModelFiles(
    const std::filesystem::path &varPath
) {

    /* this is the list of all sub directories */
    FileList bodyDirs;
    bodyDirs = listDirectories(varPath);

    /* this vector should store all of the files*/
    FileList files;
    FileList dirFiles;
    for (const auto& dir : bodyDirs) {
        dirFiles = listFiles(dir);
        files.insert(files.end(), dirFiles.begin(), dirFiles.end());
    }
    
    return files;

}

VariableModelTuple getVariableModelFileTuple(
    const std::filesystem::path &modelPath
) {
    std::string model = modelPath.stem().string();
    std::string body = modelPath.parent_path().stem().string();
    return std::make_tuple(model,body,modelPath);
}



VariableModelTuples listVariableModels(
    const std::filesystem::path &varPath
) {
    FileList files = listAllVariableModelFiles(varPath);

    VariableModelTuples out;

    for (auto &modelPath : files) {
        out.push_back(getVariableModelFileTuple(modelPath));
    }
    return out;
}


VariableModelEntry readModelEntry(std::string line) {

    std::vector<std::string> parts = splitByWhitespace(line);
    VariableModelEntry out = {
        parts[0],std::stoi(parts[1]),std::stof(parts[2])
    };
    return out;
}

VariableModel readVariableModelFile(
    std::filesystem::path &modelFile
) {
    std::vector<VariableModelEntry> out;

    std::ifstream vFile(modelFile);
    std::string line;

    VariableModelEntry entry;


    while (std::getline(vFile, line)) {
        entry = readModelEntry(line);
        out.push_back(entry);
    }

    return out;
}

std::string formatVariableModel(VariableModelTuple modelTuple) {

    VariableModel model = readVariableModelFile(std::get<2>(modelTuple));
    std::string name = std::get<0>(modelTuple);
    std::string body = std::get<1>(modelTuple);

    std::ostringstream out;

    out << "/* Body : " << body << " ---  Model : " << name << " */\n";
    out << "variableModelList& _var_model_" << name << "() {\n";
    out << "\tstatic const std::string name = \"" << name << "\";\n";
    out << "\tstatic const std::string body = \"" << body << "\";\n";
    out << "\tstatic const std::vector<std::string> models = {\n";
    for (auto &entry : model) {
        out << "\t\t\"" << entry.model << "\",\n";
    }
    out << "\t};\n";
    out << "\tstatic const std::vector<int> date = {\n";
    for (auto &entry : model) {
        out << "\t\t" << entry.date << ",\n";
    }
    out << "\t};\n";    
    out << "\tstatic const std::vector<double> ut = {\n";
    for (auto &entry : model) {
        out << "\t\t" << std::setprecision(2) << std::setw(5) << entry.ut << ",\n";
    }
    out << R"(
    };
    std::vector<double> unixt = getUnixTime(date,ut);
    std::vector<coeffStruct> coeffs = getModelCoeffs(models);
    static variableModelList out = {
        name,body,models,date,ut,unixt,coeffs
    };
    \treturn out;
};

)";

    return out.str();
}

std::string formatVariableModelProto(VariableModelTuple modelTuple) {

    std::string name = std::get<0>(modelTuple);

    std::ostringstream out;

    out << "variableModelList& _var_model_" << name << "();\n";

    return out.str();
}

std::string getVariableModelPrototypes(VariableModelTuples models) {

    std::ostringstream out;

    for (auto &model : models) {
        out << formatVariableModelProto(model);
    }
    out << "\n";

    return out.str();
}

std::string getVariableModelDefinitions(VariableModelTuples models) {

    std::ostringstream out;

    for (auto &model : models) {
        out << formatVariableModel(model);
    }
    out << "\n";

    return out.str();
}

std::string getVariableModelHeader(VariableModelTuples models) {

    std::string header = R"(
#ifndef __VARIABLE_H__
#define __VARIABLE_H__
#include <string>
#include <vector>
#include "coeffs.h"

typedef struct variableModelList {
	std::string name;
    std::string body;
	std::vector<std::string> models;
	std::vector<int> date;
	std::vector<double> ut;
	std::vector<double> unixt;
	std::vector<coeffStruct> coeffs;
} variableModelList;

typedef variableModelList& (*variableModelListFunc)();
)";

    std::ostringstream out;
    out << header;
    out << getVariableModelPrototypes(models);
    out << "#endif";

    return out.str();

}


std::string getVariableModelCode(VariableModelTuples models) {


    std::ostringstream out;
    out << "#include \"variable.h\"\n\n";
    out << getVariableModelDefinitions(models);
    out << "#endif";

    return out.str();

}

void saveVariableHeader(
    VariableModelTuples models,
    std::filesystem::path srcPath
) {
    std::filesystem::path filePath = srcPath;
    filePath /= "variable.h";
    std::cout << "Saving variable model header:" << std::endl;
    std::cout << "\t" << filePath << std::endl;

    std::ofstream file(filePath);
    file << getVariableModelHeader(models);
    file.close();
}

void saveVariableCode(
    VariableModelTuples models,
    std::filesystem::path srcPath
) {
    std::filesystem::path filePath = srcPath;
    filePath /= "variable.cc";
    std::cout << "Saving variable model code:" << std::endl;
    std::cout << "\t" << filePath << std::endl;

    std::ofstream file(filePath);    
    file << getVariableModelCode(models);
    file.close();
}


void saveVariable(
    std::filesystem::path dataPath,
    std::filesystem::path srcPath
    ) {

    std::filesystem::path varPath = dataPath;
    varPath /= "variable";

    VariableModelTuples models = listVariableModels(varPath);

    saveVariableHeader(models,srcPath);
    saveVariableCode(models,srcPath);
}