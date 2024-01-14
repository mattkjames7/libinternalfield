#include "savecoeffs.h"




FileList listAllModelFiles(
    const std::filesystem::path &coeffDir
) {

    /* this is the list of all sub directories */
    FileList bodyCoeffDirs;
    bodyCoeffDirs = listDirectories(coeffDir);

    /* this vector should store all of the files*/
    FileList files;
    FileList dirFiles;
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
    FileList files = listAllModelFiles(coeffDir);

    ModelFileTuples out;

    for (auto &modelPath : files) {
        out.push_back(getModelFileTuple(modelPath));
    }
    return out;
}

std::vector<std::string> splitString(std::string input) {

    std::vector<std::string> out;
    std::string tmp;

    for (char c : input) {
        if ((c == '\t') || (c == ' ') || (c == '\n')) {
            if (tmp.length() > 0) {
                out.push_back(tmp);
                tmp.clear();
            }
        } else {
            tmp += c;
        }
    }
    if (tmp.length() > 0) {
        out.push_back(tmp);
    }
    
    return out;
}


FileParams readFileParams(std::filesystem::path coeffFile) {

    FileCoeffs data;
    std::ifstream cFile(coeffFile);
    //std::cout << "reading file " << coeffFile << std::endl;
    if (!cFile.is_open()) {
        //std::cout << "no data "<< std::endl;
        return std::make_tuple(data,0.0,0);
    }

    double rScale = 1.0;
    int maxDegree = -1;
    int defaultDegree = -1;

    std::string rscalePrefix = "#Rscale";
    std::string defdegPrefix = "#DefaultDegree";
    std::string error;

    std::string line;
    std::istringstream liness;
    FileCoeff tmp;
    std::vector<std::string> substrs;
    while (std::getline(cFile, line)) {
        liness.clear();
        
        
        if (line.compare(0, rscalePrefix.length(), rscalePrefix) == 0) {
            liness.str(line.substr(rscalePrefix.length()));
            try {
                
                if (!(liness >> rScale)) {
                    error = "File formatting error\n";
                    error += "File: ";
                    error += coeffFile.string();
                    error += " (#Rscale)\n";
                    throw std::runtime_error(error);
                }
            } catch (const std::exception &e) {
                //std::cerr << e.what();
            }
        } else if (line.compare(0, defdegPrefix.length(), defdegPrefix) == 0) {
            liness.str(line.substr(defdegPrefix.length()));
            try {
                //defaultDegree = stoi(liness.str());
                if (!(liness >> defaultDegree)) {
                    error = "File formatting error\n";
                    error += "File: ";
                    error += coeffFile.string();
                    error += " (#DefaultDegree)\n";
                    throw std::runtime_error(error);
                }
            } catch (const std::exception &e) {
                //std::cerr << e.what();
            }
        } else {
            try {
                substrs = splitString(line);
                if (substrs.size() == 4) {
                    tmp.gh = substrs[0].c_str()[0];
                    tmp.n = stoi(substrs[1]) ;
                    tmp.m = stoi(substrs[2]);
                    tmp.val = stod(substrs[3]);
                    data.push_back(tmp);
                } //else {
                    //std::cout << substrs.size() << std::endl;
                //}
            } catch (const std::exception &e) {
                //std::cerr << e.what();
            }

        }
    }
    cFile.close();

    if (maxDegree == -1) {
        for (auto &d : data) {
            if (d.m > maxDegree){
                maxDegree = d.m;
            } 
            if (d.n > maxDegree){
                maxDegree = d.n;
            } 
        }
    }

    if (defaultDegree == -1) {
        defaultDegree = maxDegree;
    }

    return std::make_tuple(data,rScale,defaultDegree);
}


ModelDef getModelDefinition(ModelFileTuple model) {

    std::filesystem::path coeffFile = std::get<2>(model);

    FileParams params = readFileParams(coeffFile);
    FileCoeffs coeffs = std::get<0>(params);

    ModelDef def;
    def.name = std::get<0>(model);
    def.body = std::get<1>(model);
    def.rscale = std::get<1>(params);
    def.ndef = std::get<2>(params);
    def.nmax = 0;
    for (auto &p : coeffs) {
        if (p.n > def.nmax) {
            def.nmax = p.n;
        }
        if (p.m > def.nmax) {
            def.nmax = p.m;
        }
    }

    int i, j;
    
    def.len = 0;
    for (i=1;i<=def.nmax;i++) {
        for (j=0;j<=i;j++) {
            def.n.push_back(i);
            def.m.push_back(j);
            def.g.push_back(0.0);
            def.h.push_back(0.0);
            def.len++;
        }
    }

    int pos;
    for (i=0;i<coeffs.size();i++) {
        pos = coeffs[i].m - 1;
        for (j=0;j<coeffs[i].n;j++) {
            pos += (1 + j);
        } 
        if (coeffs[i].gh == 'g') {
            def.g[pos] = coeffs[i].val;
        } else {
            def.h[pos] = coeffs[i].val;
        }
    }

    return def;

}

std::string formatInts(std::vector<int> x) {

    int w = 4;
    int nPerLine = 16;
    int n = x.size();
    std::ostringstream oss;
    int i;

    for (i=0;i<n;i++) {
        if ((i % nPerLine) == 0) {
            oss << "\t\t";
        }
        oss << std::setw(w) << x[i] << ",";
        if ((((i + 1) % nPerLine) == 0) || (i == (n-1))) {
            oss << std::endl;
        }
    }

    return oss.str();

}

std::string formatDoubles(std::vector<double> x) {

    int w = 14;
    int nPerLine = 72/w;
    int n = x.size();
    std::ostringstream oss;
    int i;

    for (i=0;i<n;i++) {
        if ((i % nPerLine) == 0) {
            oss << "\t\t";
        }
        oss << std::setw(w) << std::setprecision(6) << std::fixed << x[i] << ",";
        if ((((i + 1) % nPerLine) == 0) || (i == (n-1))) {
            oss << std::endl;
        }
    }

    return oss.str();

}

std::string getModelDefinitionString(ModelFileTuple model) {

    ModelDef mdef = getModelDefinition(model);

    std::ostringstream oss;
    oss << "/* Body : " << mdef.body << " ---  Model : " << mdef.name << " */\n";
    oss << "coeffStruct& _model_coeff_" << mdef.name << "() {\n";
    oss << "\tstatic const std::string name = \"" << mdef.name << "\";\n";
    oss << "\tstatic const std::string body = \"" << mdef.body << "\";\n";
    oss << "\tstatic const int len = " << mdef.len << ";\n";
    oss << "\tstatic const int nmax = " << mdef.nmax << ";\n";
    oss << "\tstatic const int ndef = " << mdef.ndef << ";\n";
    oss << "\tstatic const double rscale = " << std::fixed << std::setw(27) 
        << std::setprecision(25) << mdef.rscale << ";\n";
    oss << "\tstatic const std::vector<int> n = {\n";
    oss << formatInts(mdef.n);
    oss << "\t};\n";
    oss << "\tstatic const std::vector<int> m = {\n";
    oss << formatInts(mdef.m);
    oss << "\t};\n";
    oss << "\tstatic const std::vector<double> g = {\n";
    oss << formatDoubles(mdef.g);
    oss << "\t};\n";
    oss << "\tstatic const std::vector<double> h = {\n";
    oss << formatDoubles(mdef.h);
    oss << "\t};\n";
    oss << "\tstatic coeffStruct out = {\n";
    oss << "\t\tname, body, len, nmax, ndef, rscale, n, m, g, h\n";
    oss << "\t};\n";
    oss << "\treturn out;\n";
    oss << "}\n\n"; 
    return oss.str();
}


std::string getAllModelDefinitionStrings(ModelFileTuples models) {

    std::ostringstream modelDefines;
    modelDefines << "/*--------------------------- Model Definitions-----------------------*/\n\n";

    std::string modelDef;

    for (auto &model : models) {
        modelDef = getModelDefinitionString(model);
        modelDefines << modelDef;
        modelDefines << "\n\n";
    }

    return modelDefines.str();
}

std::string coeffStructDef() {

    std::string out = R"(
typedef struct {
    const std::string name;
    const std::string body;
    const int len;
    const int nmax;
    const int ndef;
    const double rscale;
    const std::vector<int> n;
    const std::vector<int> m;
    const std::vector<double> g;
    const std::vector<double> h;
} coeffStruct;

)";
    return out;
}

std::string getHeaderExterns(ModelFileTuples models) {

    std::ostringstream oss;
    oss << "/* functions to return model coefficients */";
    for (auto &model : models) {
        oss << "extern coeffStruct& _model_coeff";
        oss << std::get<0>(model);
        oss << "();\n";
    }
    oss << "\n";
    return oss.str();
}

std::string formatModelStringList(std::vector<std::string> modelNames) {

    /* get longest string length */
    int l = 0;
    for (auto name : modelNames) {
        if (name.length() > l) {
            l = name.length();
        }
    }

    /* create formatted string */
    int w = l + 4;
    int nPerLine = 72/w;
    int n = modelNames.size();
    std::ostringstream oss;
    int i, j;

    for (i=0;i<n;i++) {
        if ((i % nPerLine) == 0) {
            oss << "\t\t";
        }
        l = w - modelNames[i].length();
        oss << "\"" << modelNames[i] << "\", ";
        for (j=0;j<l;j++) {
            oss << " ";
        }
        if ((((i + 1) % nPerLine) == 0) || (i == (n-1))) {
            oss << std::endl;
        }
    }

    return oss.str();

}

std::string getModelNameFunction(ModelFileTuples models) {

    /* get the list of models found */
    std::vector<std::string> modelNames;
    for (auto &model : models) {
        modelNames.push_back(std::get<0>(model));
    }

    /* define the function */
    std::ostringstream oss;
    oss << "std::vector<std::string> getModelNames() {\n";
    oss << "\tstatic std::vector<std::string> modelNames = {\n";
    oss << formatModelStringList(modelNames);
    oss << "\t};\n";
    oss << "\treturn modelNames;\n";
    oss << "}\n\n";

    return oss.str();
}


std::string getModelCoeffStructHeader() {

    std::string out = R"(
/***********************************************************************
 * NAME : getModelCoeffStruct(Model)
 *
 * DESCRIPTION : Function to return a structure containing model 
        coefficients.
 *		
 * INPUTS : 
 *		std::string Model	Model name (use lower case!).
 *
 * RETURNS :
 *		coeffStructFunc	cstr    Model coefficient function.
 *
 **********************************************************************/
coeffStructFunc getModelCoeffStruct(std::string Model);

/***********************************************************************
 * NAME : getModelCoeffStruct(Model)
 *
 * DESCRIPTION : Function to return a structure containing model 
        coefficients.
 *		
 * INPUTS : 
 *		const char *Model	Model name (use lower case!).
 *
 * RETURNS :
 *		coeffStructFunc	cstr    Model coefficient function.
 *
 **********************************************************************/
coeffStructFunc getModelCoeffStruct(const char *Model);

)";
    return out;
}


std::string getCoeffMapFunction(ModelFileTuples models) {
    std::ostringstream oss;
    oss << "std::map<std::string,coeffStructFunc> getCoeffMap() {\n";
    oss << "\tstatic std::map<std::string,coeffStructFunc> coeffMap = {\n";

    std::string name;
    for (auto &model : models) {
        name = std::get<0>(model);
        oss << "\t\t{\"";
        oss << name;
        oss << "\", _model_coeff_";
        oss << name;
        oss << "},\n";
    }

    oss << "\t};\n";
    oss << "\treturn coeffMap;\n";
    oss << "}\n\n";

    return oss.str();
}


std::string getModelCoeffStructFunctions() {

    std::string out = R"(
/***********************************************************************
 * NAME : getModelCoeffStruct(Model)
 *
 * DESCRIPTION : Function to return a structure containing model 
        coefficients.
 *		
 * INPUTS : 
 *		std::string Model	Model name (use lower case!).
 *
 * RETURNS :
 *		coeffStructFunc	cstr    Model coefficient function.
 *
 **********************************************************************/
coeffStructFunc getModelCoeffStruct(std::string Model) {
    std::map<std::string,coeffStructFunc> coeffMap = getCoeffMap();
    return coeffMap[Model];
}

/***********************************************************************
 * NAME : getModelCoeffStruct(Model)
 *
 * DESCRIPTION : Function to return a structure containing model 
        coefficients.
 *		
 * INPUTS : 
 *		const char *Model	Model name (use lower case!).
 *
 * RETURNS :
 *		coeffStructFunc	cstr    Model coefficient function.
 *
 **********************************************************************/
coeffStructFunc getModelCoeffStruct(const char *Model) {
    std::map<std::string,coeffStructFunc> coeffMap = getCoeffMap();
    return coeffMap[Model];
}

)";
    return out;
}

void writeCoeffsCC(ModelFileTuples models,std::filesystem::path srcPath) {
    
    /* get the model name function */
    std::string modelNameFunction = getModelNameFunction(models);

    /* collect model definitions */
    std::string allDefs = getAllModelDefinitionStrings(models);

    /* save everything to the file */
    std::filesystem::path filePath = srcPath;
    filePath /= "coeffs.cc";
    std::cout << "Saving model coefficient code:" << std::endl;
    std::cout << "\t" << filePath << std::endl;

    std::ofstream outFile(filePath);
    outFile << "#include \"coeffs.h\"\n\n";
    outFile << modelNameFunction;
    outFile << allDefs;
    outFile << getCoeffMapFunction(models);
    outFile << getModelCoeffStructFunctions();
    outFile.close();


}



void writeCoeffsH(ModelFileTuples models,std::filesystem::path srcPath) {
    
    /* model coefficient functions */
    std::string headerExterns = getHeaderExterns(models);

    /* collect model definitions */
    std::string coeffStruct = coeffStructDef();

    /* save everything to the file */
    std::filesystem::path filePath = srcPath;
    filePath /= "coeffs.h";
    std::cout << "Saving model coefficient header:" << std::endl;
    std::cout << "\t" << filePath << std::endl;

    std::ofstream outFile(filePath);
    outFile << "#ifndef __COEFFS_H__\n";
    outFile << "#define __COEFFS_H__\n";
    outFile << "#include <vector>\n";
    outFile << "#include <string>\n";
    outFile << "#include <map>\n\n";
    outFile << coeffStruct;
    outFile << "typedef coeffStruct& (*coeffStructFunc)();\n\n";
    outFile << "/* list of model names */\n";
    outFile << "std::vector<std::string> getModelNames();\n\n";
    outFile << headerExterns;
    outFile << "/* map model names to the structure containing the coefficients */\n";
    outFile << "std::map<std::string,coeffStructFunc> getCoeffMap();\n\n";
    outFile << getModelCoeffStructHeader();
    outFile << "#endif\n";
    outFile.close();


}


void saveCoeffs(
    std::filesystem::path dataPath,
    std::filesystem::path srcPath
) {

    /* get the coefficient paths */
    std::filesystem::path coeffPath = dataPath;
    coeffPath /= "coeffs";
    
    /* check if it exists */
    if (
        (std::filesystem::exists(coeffPath) == false) || 
        (std::filesystem::is_directory(coeffPath) == false)
    ) {
        std::cerr << coeffPath << " is not a directory or does not exist" << std::endl;
        return;
    }


    /* get a list of the subdirectories to scan */
    // FileList files = listAllModelFiles(coeffPath);
    // int i, n;
    // n = files.size();
    // for (i=0;i<n;i++) {
    //     std::cout << files[i] << std::endl;
    // }

    ModelFileTuples models = listModels(coeffPath);
    std::cout << "Found " << models.size() << " model definitions." <<  std::endl;

    // for (auto &model : models) {
    //     std::cout << "Model: " << std::get<0>(model) << ", ";
    //     std::cout << "Body: " << std::get<1>(model) << ", ";
    //     std::cout << "Model File: " << std::get<2>(model);
    //     std::cout << std::endl;
    // }

    //FileParams params = readFileParams(files[0]);

    // FileCoeffs coeffs = std::get<0>(params);
    // for (auto &c : coeffs) {
    //     std::cout << c.gh << " " << c.m << " " << c.n << " " << c.val << std::endl;
    // }
    // std::cout << coeffs.size() << std::endl;

    // std::string example = getModelDefinitionString(models[0]);
    // std::cout << example << std::endl;

    writeCoeffsCC(models,srcPath);
    writeCoeffsH(models,srcPath);
    
}
