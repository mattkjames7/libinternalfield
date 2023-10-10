#include "savecoeffs.h"


std::vector<std::filesystem::path> listDirectories(
    const std::filesystem::path &startDir; 
) {
    std::vector<std::filesystem::path> subDirs;

    for (const auto& entry : std::filesystem::directory_iterator(startDir)) {
        if (std::filesystem::is_directory(entry.status())) {
            subDirs.push_back(entry.path());
        }
    }

    return subDirs;
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





}
