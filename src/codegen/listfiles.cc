#include "listfiles.h"


FileList listDirectories(
    const std::filesystem::path &startDir 
) {
    FileList subDirs;

    for (const auto& entry : std::filesystem::directory_iterator(startDir)) {
        if (std::filesystem::is_directory(entry.status())) {
            subDirs.push_back(entry.path());
        }
    }

    return subDirs;
}

FileList listFiles(
    const std::filesystem::path &startDir 
) {
    FileList files;

    for (const auto& entry : std::filesystem::directory_iterator(startDir)) {
        if (std::filesystem::is_regular_file(entry.status())) {
            if (entry.path().extension() == ".dat") {
                files.push_back(entry.path());
            }
        }
    }

    return files;
}
