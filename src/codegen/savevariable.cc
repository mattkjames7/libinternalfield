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


VariableModel readVariableModelFile(
    std::filesystem::path &modelFile
) {
    std::vector<VariableModelEntry> out;

    std::ifstream vFile(modelFile);
    std::string line;

    while (std::getline(vFile, line)) {
        
    }

}


void saveVariable(std::filesystem::dataPath) {

    std::filesystem::path varPath = dataPath;
    varPath /= "variable";


}