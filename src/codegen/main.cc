#include "main.h"



int main(int argc, char *argv[]) {

    /* check for the starting directory */
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_data> " << std::endl;
        return 1;
    }

    
    std::filesystem::path dataPath = argv[1];
    std::filesystem::path srcPath = dataPath.parent_path();
    srcPath /= "src";

    /* start by saving individual IGRF models */
    saveIGRFModels(dataPath);

    /* now create coefficient files */
    saveCoeffs(dataPath);

    /* save model function files */
    saveModels(dataPath);

    /* save variable models */
    saveVariable(dataPath);

    /* generate the header for the library */
    saveLibHeader(srcPath);

    return 0;

}