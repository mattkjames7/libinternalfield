#ifndef __LISTFILES_H__
#define __LISTFILES_H__
#include <vector>
#include <filesystem>


typedef std::vector<std::filesystem::path> FileList;
FileList listDirectories(
    const std::filesystem::path &startDir 
);
FileList listFiles(
    const std::filesystem::path &startDir 
);

#endif
