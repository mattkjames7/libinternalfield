#include "savecoeffs.h"


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
    std::cout << "reading file " << coeffFile << std::endl;
    if (!cFile.is_open()) {
        std::cout << "no data "<< std::endl;
        return std::make_tuple(data,0.0,0);
    }

    double rScale = 1.0;
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
                std::cerr << e.what();
            }
        } else if (line.compare(0, defdegPrefix.length(), defdegPrefix) == 0) {
            liness.str(line.substr(defdegPrefix.length()));
            try {
                if (!(liness >> rScale)) {
                    error = "File formatting error\n";
                    error += "File: ";
                    error += coeffFile.string();
                    error += " (#DefaultDegree)\n";
                    throw std::runtime_error(error);
                }
            } catch (const std::exception &e) {
                std::cerr << e.what();
            }
        } else {
            try {
                substrs = splitString(line);
                if (substrs.size() == 4) {
                    tmp.gh = substrs[0].c_str()[0];
                    tmp.m = stoi(substrs[1]) ;
                    tmp.n = stoi(substrs[2]);
                    tmp.val = stod(substrs[3]);
                    data.push_back(tmp);
                } else {
                    std::cout << substrs.size() << std::endl;
                }
            } catch (const std::exception &e) {
            }

        }
    }
    cFile.close();

    if (defaultDegree == -1) {
        for (auto &d : data) {
            if (d.m > defaultDegree){
                defaultDegree = d.m;
            } 
            if (d.n > defaultDegree){
                defaultDegree = d.n;
            } 
        }
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
    int nPerLine = 80/w;
    int n = x.size();
    std::ostringstream oss;
    int i;

    for (i=0;i<n;i++) {
        if ((i % nPerLine) == 0) {
            oss << "\t\t";
        }
        oss << std::setw(w) << std::setprecision(6) << [i] << ",";
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
    oss << "\tstatic const int len = " << mdef.len << ";\n";
    oss << "\tstatic const int nmax = " << mdef.nmax << ";\n";
    oss << "\tstatic const int ndef = " << mdef.ndef << ";\n";
    oss << "\tstatic const int rscale = " << std::fixed << std::setw(27) 
        << std::setprecision(25) << mdef.rscale << ";\n";
    oss << "\tstatic const std::vector<int> n = {\n";
    oss << formatInts(mdef.n);
    oss << "\t};\n";
    oss << "\tstatic const std::vector<int> m = {\n";
    oss << formatInts(mdef.n);
    oss << "\t};\n";
    oss << "\tstatic const std::vector<double> g = {\n";
    oss << formatDoubles(mdef.g);
    oss << "\t};\n";
    oss << "\tstatic const std::vector<double> h = {\n";
    oss << formatDoubles(mdef.h);
    oss << "\t};\n";
    oss << "}\n\n"; 
    return oss.str();
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
    FileList files = listAllModelFiles(coeffPath);
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

    FileParams params = readFileParams(files[0]);

    FileCoeffs coeffs = std::get<0>(params);
    for (auto &c : coeffs) {
        std::cout << c.gh << " " << c.m << " " << c.n << " " << c.val << std::endl;
    }
    std::cout << coeffs.size() << std::endl;

    std::string example = getModelDefinitionString(models[0]);
    std::cout << example << std::endl;

    return 0;

}
