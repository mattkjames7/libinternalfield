#include "modelindex.h"

FileList listAllModelFiles(const std::filesystem::path &coeffDir) {

    FileList bodyCoeffDirs;
    bodyCoeffDirs = listDirectories(coeffDir);

    FileList files;
    FileList dirFiles;
    for (const auto &dir : bodyCoeffDirs) {
        dirFiles = listFiles(dir);
        files.insert(files.end(), dirFiles.begin(), dirFiles.end());
    }

    return files;
}

ModelFileTuple getModelFileTuple(const std::filesystem::path &modelPath) {
    std::string model = modelPath.stem().string();
    std::string body = modelPath.parent_path().stem().string();
    return std::make_tuple(model, body, modelPath);
}

ModelFileTuples listModels(const std::filesystem::path &coeffDir) {
    FileList files = listAllModelFiles(coeffDir);

    ModelFileTuples out;

    for (auto &modelPath : files) {
        out.push_back(getModelFileTuple(modelPath));
    }
    return out;
}
