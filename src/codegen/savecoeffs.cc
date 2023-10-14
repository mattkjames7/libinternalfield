#include "savecoeffs.h"

typedef std::tuple<std::string,std::string,std::filesystem::path> ModelFileTuple;
typedef std::vector<ModelFileTuple> ModelFileTuples;

std::vector<std::filesystem::path> listDirectories(
    const std::filesystem::path &startDir 
) {
    std::vector<std::filesystem::path> subDirs;

    for (const auto& entry : std::filesystem::directory_iterator(startDir)) {
        if (std::filesystem::is_directory(entry.status())) {
            subDirs.push_back(entry.path());
        }
    }

    return subDirs;
}

std::vector<std::filesystem::path> listFiles(
    const std::filesystem::path &startDir 
) {
    std::vector<std::filesystem::path> files;

    for (const auto& entry : std::filesystem::directory_iterator(startDir)) {
        if (std::filesystem::is_regular_file(entry.status())) {
            files.push_back(entry.path());
        }
    }

    return files;
}


std::vector<std::filesystem::path> listAllModelFiles(
    const std::filesystem::path &coeffDir
) {

    /* this is the list of all sub directories */
    std::vector<std::filesystem::path> bodyCoeffDirs;
    bodyCoeffDirs = listDirectories(coeffDir);

    /* this vector should store all of the files*/
    std::vector<std::filesystem::path> files;
    std::vector<std::filesystem::path> dirFiles;
    for (const auto& dir : bodyCoeffDirs) {
        dirFiles = listFiles(dir);
        files.insert(files.end(), dirFiles.begin(), dirFiles.end());
    }
    
    return files;

}


ModelFileTuple getModelFileTuple(
    const std::filesystem::path &modelPath
) {
    std::string model = modelPath.stem().string();
    std::string body = modelPath.parent_path().stem().string();
    return std::make_tuple(model,body,modelPath);
}


ModelFileTuples listModels(
    const std::filesystem::path &coeffDir
) {
    std::vector<std::filesystem::path> files = listAllModelFiles(coeffDir);

    ModelFileTuples out;

    for (auto &modelPath : files) {
        out.push_back(getModelFileTuple(modelPath));
    }
    return out;
}

int main(int argc, char *argv[]) {

    /* check for the starting directory */
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_data> " << std::endl;
        return 1;
    }

    /* get the coefficient paths */
    std::filesystem::path dataPath = argv[1];
    std::filesystem::path coeffPath = dataPath;
    coeffPath /= "coeffs";
    
    /* check if it exists */
    if (
        (std::filesystem::exists(coeffPath) == false) || 
        (std::filesystem::is_directory(coeffPath) == false)
    ) {
        std::cerr << coeffPath << " is not a directory or does not exist" << std::endl;
        return 2;
    }


    /* get a list of the subdirectories to scan */
    std::vector<std::filesystem::path> files = listAllModelFiles(coeffPath);
    int i, n;
    n = files.size();
    for (i=0;i<n;i++) {
        std::cout << files[i] << std::endl;
    }

    ModelFileTuples models = listModels(coeffPath);
    for (auto &model : models) {
        std::cout << "Model: " << std::get<0>(model) << ", ";
        std::cout << "Body: " << std::get<1>(model) << ", ";
        std::cout << "Model File: " << std::get<2>(model);
        std::cout << std::endl;
    }

    return 0;

}
