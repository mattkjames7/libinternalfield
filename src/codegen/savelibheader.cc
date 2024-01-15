#include "savelibheader.h"


std::string getLibHeaderTop() {
    std::string out = R"(
#ifndef __LIBINTERNALFIELD_H__
#define __LIBINTERNALFIELD_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __cplusplus
#include <vector>
#include <map>
#include <string>
#else 
#include <string.h>
#endif



#define INTERNALFIELD_VERSION_MAJOR 1
#define INTERNALFIELD_VERSION_MINOR 2
#define INTERNALFIELD_VERSION_PATCH 0

/* this is used in both C and C++*/
typedef void (*modelFieldPtr)(double,double,double,double*,double*,double*);

#ifdef __cplusplus
extern "C" {
#endif

)";
    return out;
}


std::vector<std::string> removeDirectives(const std::vector<std::string>& lines) {
    std::vector<std::string> filteredLines;

    for (const auto& line : lines) {
        // Check if the line starts with '#' and skip it if it does
        if (line.find("#") != 0) {
            filteredLines.push_back(line);
        }
    }

    return filteredLines;
}

std::vector<std::string> readASCII(std::filesystem::path fileName) {
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> out;
    while (std::getline(file,line)) {
        out.push_back(line+"\n");
    } 
    file.close();
    return out;
}


StrVecPair splitHeaderDefs(const std::vector<std::string>& lines) {
    std::vector<std::string> cCode;
    std::vector<std::string> cppCode;

    bool isC = false;
    for (const auto& line : lines) {
        std::string trimmedLine = trimString(line); // Add logic to trim whitespace if necessary
        if (isC && trimmedLine == "}") {
            isC = false;
        }
        if (isC) {
            cCode.push_back(line);
        } else {
            cppCode.push_back(line);
        }
        if (trimmedLine.find("extern \"C\"") != std::string::npos) {
            isC = true;
        }
    }

    return {cCode, cppCode};
}


std::vector<std::string> extractInternalH() {

    std::vector<std::string> lines = readASCII("../internal.h");
    std::vector<std::string> out = removeDirectives(lines);
    return out;
}

std::vector<std::string> extractInternalModelH() {

    std::vector<std::string> lines = readASCII("../internalmodel.h");
    std::vector<std::string> out = removeDirectives(lines);
    return out;
}

StrVecPair extractModelsH() {

    std::vector<std::string> lines = readASCII("../models.h");
    StrVecPair code = splitHeaderDefs(lines);
    std::vector<std::string> cCode = code.first;
    std::vector<std::string> ccCode = code.second;
    std::vector<std::string> cOut = removeDirectives(cCode);
    std::vector<std::string> ccTmp = removeDirectives(ccCode);
    std::vector<std::string> ccOut;
    for (auto &cct : ccTmp) {
        if (cct.find("typedef void (*modelFieldPtr)(double,double,double,double*,double*,double*);") == std::string::npos) {
            ccOut.push_back(cct);
        }
    }
    return {cOut,ccOut};
}

StrVecPair extractLibinternalH() {

    std::vector<std::string> lines = readASCII("../libinternal.h");
    StrVecPair code = splitHeaderDefs(lines);
    std::vector<std::string> cCode = code.first;
    std::vector<std::string> ccCode = code.second;
    std::vector<std::string> cOut = removeDirectives(cCode);
    std::vector<std::string> ccOut = removeDirectives(ccCode);

    return {cOut,ccOut};
}

std::vector<std::string> extractCoeffsH() {

    std::vector<std::string> lines = readASCII("../coeffs.h");
    std::vector<std::string> out = removeDirectives(lines);
    return out;
}

std::vector<std::string> extractListmapkeysH() {

    std::vector<std::string> lines = readASCII("../listmapkeys.h");
    std::vector<std::string> out = removeDirectives(lines);
    return out;
}

std::string stringVectorToString(std::vector<std::string> strVec) {

    std::ostringstream out;
    for (auto &str : strVec) {
        out << str;
    }
    return out.str();
}


std::string generateLibHeader() {

    std::ostringstream out;
    std::ostringstream cCode;
    std::ostringstream ccCode;
    StrVecPair codePair;
    std::vector<std::string> cVec, ccVec;

    /* add the includes and stuff at the top */
    out << getLibHeaderTop();

    /* start with coeffs.h */
    ccVec = extractCoeffsH();
    ccCode << stringVectorToString(ccVec);
    ccVec.clear();

    /* internal.h */
    ccVec = extractInternalH();
    ccCode << stringVectorToString(ccVec);
    ccVec.clear();

    /* models.h */
    codePair = extractModelsH();
    cCode << stringVectorToString(codePair.first);
    ccCode << stringVectorToString(codePair.second);

    /* listmapkeys.h */
    ccVec = extractListmapkeysH();
    ccCode << stringVectorToString(ccVec);
    ccVec.clear();

    /* internalmodel.h */
    ccVec = extractInternalModelH();
    ccCode << stringVectorToString(ccVec);
    ccVec.clear();

    /* libinternal.h */
    codePair = extractLibinternalH();
    cCode << stringVectorToString(codePair.first);
    ccCode << stringVectorToString(codePair.second);

    /* add the C-compatible bits to the extern C section */
    out << cCode.str();

    /* close the extern C bit and add the C++ only code */
    out << "#ifdef __cplusplus\n";
    out << "}\n\n";
    out << ccCode.str();
    out << "#endif\n";
    out << "#endif\n";

    return out.str();

}

void saveLibHeader(std::filesystem::path srcPath) {

    std::string headerCode = generateLibHeader();

    std::filesystem::path headerPath = srcPath.parent_path();
    headerPath /= "include/internalfield.h";
    std::cout << "Saving library header: " << std::endl;
    std::cout << "\t" << headerPath << std::endl;
    std::ofstream file(headerPath);
    file << headerCode;
    file.close();
}