#include "main.h"



int main(int argc, char *argv[]) {

    /* check for the starting directory */
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_data> " << std::endl;
        return 1;
    }

    
    std::filesystem::path dataPath = argv[1];

    /* start by saving individual IGRF models */
    saveIGRFModels(dataPath);

    /* now create coefficient files */
    saveCoeffs(dataPath);

    /* save model function files */
    saveModels(dataPath);

    return 0;

}