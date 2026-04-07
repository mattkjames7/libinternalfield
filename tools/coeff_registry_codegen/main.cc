#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "scalegh.h"
#include "schmidt.h"

namespace fs = std::filesystem;

struct RawCoeff {
    char gh = 'g';
    int n = 0;
    int m = 0;
    double val = 0.0;
};

struct ModelData {
    std::string name;
    std::string body;
    int len = 0;
    int nmax = 0;
    int ndef = 0;
    double rscale = 1.0;
    std::vector<int> n;
    std::vector<int> m;
    std::vector<double> g;
    std::vector<double> h;
};

struct IgrfModel {
    std::string name;
    std::vector<char> gh;
    std::vector<int> n;
    std::vector<int> m;
    std::vector<double> v;
};

static std::vector<std::string> splitTokens(const std::string &line) {
    std::vector<std::string> out;
    std::string token;
    for (char c : line) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!token.empty()) {
                out.push_back(token);
                token.clear();
            }
        } else {
            token.push_back(c);
        }
    }
    if (!token.empty()) {
        out.push_back(token);
    }
    return out;
}

static std::vector<std::string> readTextLines(const fs::path &filePath) {
    std::ifstream in(filePath);
    if (!in.is_open()) {
        throw std::runtime_error("failed to open file: " + filePath.string());
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
    return lines;
}

static std::vector<int> listIgrfModelYears(const std::vector<std::string> &lines) {
    if (lines.size() < 6) {
        throw std::runtime_error("IGRF file is too short");
    }

    const std::vector<std::string> names = splitTokens(lines[3]);
    if (names.size() < 5) {
        throw std::runtime_error("unexpected IGRF header format");
    }

    std::vector<int> out;
    for (std::size_t i = 3; i + 1 < names.size(); i++) {
        out.push_back(std::stoi(names[i]));
    }

    const std::string &range = names.back();
    const std::size_t dashPos = range.find('-');
    if (dashPos == std::string::npos) {
        throw std::runtime_error("unexpected IGRF final-year range format");
    }

    const int startYear = std::stoi(range.substr(0, dashPos));
    const int endYear = std::stoi(range.substr(dashPos + 1));
    out.push_back((startYear / 100) * 100 + endYear);
    return out;
}

static std::vector<std::vector<std::string>> getIgrfTable(const std::vector<std::string> &lines) {
    int nRows = static_cast<int>(lines.size()) - 4;
    std::vector<std::string> firstDataTokens = splitTokens(lines[5]);
    const int nCols = static_cast<int>(firstDataTokens.size());

    if (nCols < 4) {
        throw std::runtime_error("unexpected IGRF table format");
    }

    if (splitTokens(lines.back()).size() < static_cast<std::size_t>(nCols)) {
        nRows -= 1;
    }

    if (nRows <= 0) {
        throw std::runtime_error("IGRF table has no rows");
    }

    std::vector<std::vector<std::string>> table(
        static_cast<std::size_t>(nCols),
        std::vector<std::string>(static_cast<std::size_t>(nRows))
    );

    for (int i = 0; i < nRows; i++) {
        const std::vector<std::string> tokens = splitTokens(lines[static_cast<std::size_t>(i + 4)]);
        if (tokens.size() < static_cast<std::size_t>(nCols)) {
            throw std::runtime_error("malformed IGRF table row");
        }
        for (int j = 0; j < nCols; j++) {
            table[static_cast<std::size_t>(j)][static_cast<std::size_t>(i)] =
                tokens[static_cast<std::size_t>(j)];
        }
    }

    return table;
}

static IgrfModel fillIgrfModel(
    int modelIndex,
    int nRows,
    const std::vector<int> &modelYears,
    const std::vector<std::vector<std::string>> &table
) {
    IgrfModel model;
    model.name = "igrf" + std::to_string(modelYears[static_cast<std::size_t>(modelIndex)]);

    for (int i = 0; i < nRows; i++) {
        model.gh.push_back(table[0][static_cast<std::size_t>(i)][0]);
        model.n.push_back(std::stoi(table[1][static_cast<std::size_t>(i)]));
        model.m.push_back(std::stoi(table[2][static_cast<std::size_t>(i)]));
        model.v.push_back(std::stod(table[static_cast<std::size_t>(modelIndex + 3)][static_cast<std::size_t>(i)]));
    }

    return model;
}

static std::vector<IgrfModel> readIgrfModels(const fs::path &dataRoot) {
    const fs::path igrfFile = dataRoot / "igrf" / "igrf13coeffs.txt";
    const std::vector<std::string> lines = readTextLines(igrfFile);
    const std::vector<int> modelYears = listIgrfModelYears(lines);
    const std::vector<std::vector<std::string>> table = getIgrfTable(lines);

    const int nModels = static_cast<int>(modelYears.size());
    const int nRows = static_cast<int>(table[0].size());

    std::vector<IgrfModel> models;
    for (int i = 0; i < nModels; i++) {
        models.push_back(fillIgrfModel(i, nRows, modelYears, table));
    }

    if (nModels >= 2) {
        for (int i = 0; i < nRows; i++) {
            const std::size_t row = static_cast<std::size_t>(i);
            models[static_cast<std::size_t>(nModels - 1)].v[row] =
                models[static_cast<std::size_t>(nModels - 2)].v[row] +
                5.0 * models[static_cast<std::size_t>(nModels - 1)].v[row];
        }
    }

    return models;
}

static std::string formatIgrfLine(char gh, int n, int m, double v) {
    std::ostringstream out;
    out << gh << ' '
        << std::setw(4) << n << ' '
        << std::setw(4) << m << ' '
        << std::setw(14) << std::setprecision(6) << std::fixed << v;
    return out.str();
}

static void refreshIgrfCoeffFiles(const fs::path &coeffRoot) {
    const fs::path dataRoot = coeffRoot.parent_path();
    const std::vector<IgrfModel> models = readIgrfModels(dataRoot);

    const fs::path earthDir = coeffRoot / "earth";
    fs::create_directories(earthDir);

    for (const auto &model : models) {
        const fs::path outFile = earthDir / (model.name + ".dat");
        std::ofstream out(outFile);
        if (!out.is_open()) {
            throw std::runtime_error("failed to write file: " + outFile.string());
        }
        for (std::size_t i = 0; i < model.gh.size(); i++) {
            out << formatIgrfLine(model.gh[i], model.n[i], model.m[i], model.v[i]) << '\n';
        }
    }
}

static std::vector<fs::path> sortedSubdirs(const fs::path &root) {
    std::vector<fs::path> dirs;
    for (const auto &entry : fs::directory_iterator(root)) {
        if (entry.is_directory()) {
            dirs.push_back(entry.path());
        }
    }
    std::sort(dirs.begin(), dirs.end());
    return dirs;
}

static std::vector<fs::path> sortedFiles(const fs::path &dir) {
    std::vector<fs::path> files;
    for (const auto &entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }
    std::sort(files.begin(), files.end());
    return files;
}

static int coeffPos(int n, int m) {
    int pos = m - 1;
    for (int j = 0; j < n; j++) {
        pos += 1 + j;
    }
    return pos;
}

static ModelData parseModelFile(const fs::path &filePath) {
    std::ifstream in(filePath);
    if (!in.is_open()) {
        throw std::runtime_error("failed to open file: " + filePath.string());
    }

    ModelData out;
    out.name = filePath.stem().string();
    out.body = filePath.parent_path().stem().string();

    std::vector<RawCoeff> rows;

    std::string line;
    int defaultDegree = -1;
    int maxDegree = -1;

    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        if (line.rfind("#Rscale", 0) == 0) {
            std::istringstream iss(line.substr(7));
            if (!(iss >> out.rscale)) {
                throw std::runtime_error("invalid #Rscale line in: " + filePath.string());
            }
            continue;
        }

        if (line.rfind("#DefaultDegree", 0) == 0) {
            std::istringstream iss(line.substr(14));
            if (!(iss >> defaultDegree)) {
                throw std::runtime_error("invalid #DefaultDegree line in: " + filePath.string());
            }
            continue;
        }

        if (line[0] == '#') {
            continue;
        }

        auto tokens = splitTokens(line);
        if (tokens.size() != 4) {
            continue;
        }

        RawCoeff rc;
        rc.gh = tokens[0].empty() ? 'g' : tokens[0][0];
        rc.n = std::stoi(tokens[1]);
        rc.m = std::stoi(tokens[2]);
        rc.val = std::stod(tokens[3]);

        maxDegree = std::max(maxDegree, std::max(rc.n, rc.m));
        rows.push_back(rc);
    }

    if (maxDegree < 0) {
        throw std::runtime_error("no coefficients found in: " + filePath.string());
    }

    out.nmax = maxDegree;
    out.ndef = (defaultDegree < 0) ? maxDegree : defaultDegree;

    for (int n = 1; n <= out.nmax; n++) {
        for (int m = 0; m <= n; m++) {
            out.n.push_back(n);
            out.m.push_back(m);
            out.g.push_back(0.0);
            out.h.push_back(0.0);
        }
    }

    out.len = static_cast<int>(out.n.size());

    for (const auto &rc : rows) {
        const int pos = coeffPos(rc.n, rc.m);
        if (pos < 0 || pos >= out.len) {
            throw std::runtime_error("coefficient index out of range in: " + filePath.string());
        }
        if (rc.gh == 'g' || rc.gh == 'G') {
            out.g[pos] = rc.val;
        } else {
            out.h[pos] = rc.val;
        }
    }

    return out;
}

static std::vector<ModelData> loadAllModels(const fs::path &coeffRoot) {
    std::vector<ModelData> models;
    auto dirs = sortedSubdirs(coeffRoot);
    for (const auto &dir : dirs) {
        auto files = sortedFiles(dir);
        for (const auto &file : files) {
            models.push_back(parseModelFile(file));
        }
    }

    std::sort(models.begin(), models.end(), [](const ModelData &a, const ModelData &b) {
        if (a.name == b.name) {
            return a.body < b.body;
        }
        return a.name < b.name;
    });

    for (std::size_t i = 1; i < models.size(); i++) {
        if (models[i - 1].name == models[i].name) {
            throw std::runtime_error(
                "duplicate model name found across bodies: " + models[i].name
            );
        }
    }

    return models;
}

static std::string makeIdentifier(const std::string &name) {
    std::string out = "kModel_";
    out.reserve(out.size() + name.size());
    for (char c : name) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            out.push_back(c);
        } else {
            out.push_back('_');
        }
    }
    return out;
}

static void writeRegistryHeader(const std::vector<ModelData> &models, const fs::path &outputHeader) {
    std::vector<std::size_t> nameOrder(models.size());
    std::iota(nameOrder.begin(), nameOrder.end(), 0);
    std::sort(nameOrder.begin(), nameOrder.end(), [&models](std::size_t a, std::size_t b) {
        return models[a].name < models[b].name;
    });

    std::vector<std::string> modelIdentifiers(models.size());
    for (std::size_t i = 0; i < models.size(); i++) {
        modelIdentifiers[i] = makeIdentifier(models[i].name);
    }

    int globalNmax = 0;
    for (const auto &model : models) {
        if (model.nmax > globalNmax) {
            globalNmax = model.nmax;
        }
    }
    const std::vector<double> schmidtFlat = ComputeSchmidtFlat(globalNmax);

    std::ofstream out(outputHeader);
    if (!out.is_open()) {
        throw std::runtime_error("failed to open output file: " + outputHeader.string());
    }

    out << "#pragma once\n\n";
    out << "#include <array>\n";
    out << "#include <cstddef>\n";
    out << "#include <string_view>\n\n";

    out << "namespace internalfield::models {\n\n";

    out << "template <std::size_t N>\n";
    out << "struct ModelParams {\n";
    out << "    std::string_view name;\n";
    out << "    std::string_view body;\n";
    out << "    int nmax;\n";
    out << "    int ndef;\n";
    out << "    double rscale;\n";
    out << "    std::array<int, N> n;\n";
    out << "    std::array<int, N> m;\n";
    out << "    std::array<double, N> g;\n";
    out << "    std::array<double, N> h;\n";
    out << "    std::array<double, N> g_scaled;\n";
    out << "    std::array<double, N> h_scaled;\n";
    out << "};\n\n";

    out << "struct ModelView {\n";
    out << "    std::string_view name;\n";
    out << "    std::string_view body;\n";
    out << "    int nmax;\n";
    out << "    int ndef;\n";
    out << "    double rscale;\n";
    out << "    std::size_t len;\n";
    out << "    const int *n;\n";
    out << "    const int *m;\n";
    out << "    const double *g;\n";
    out << "    const double *h;\n";
    out << "    const double *g_scaled;\n";
    out << "    const double *h_scaled;\n";
    out << "};\n\n";

    out << "struct NameIndex {\n";
    out << "    std::string_view name;\n";
    out << "    std::size_t index;\n";
    out << "};\n\n";

    out << std::scientific << std::setprecision(16);
    for (std::size_t i = 0; i < models.size(); i++) {
        const auto &m = models[i];
        std::vector<double> gScaled;
        std::vector<double> hScaled;
        ComputeScaledGH(m.n, m.m, m.g, m.h, schmidtFlat, gScaled, hScaled);

        out << "inline constexpr ModelParams<" << m.len << "> " << modelIdentifiers[i] << " = {\n";
        out << "    \"" << m.name << "\",\n";
        out << "    \"" << m.body << "\",\n";
        out << "    " << m.nmax << ",\n";
        out << "    " << m.ndef << ",\n";
        out << "    " << m.rscale << ",\n";
        out << "    {{\n";
        for (int j = 0; j < m.len; j++) {
            out << "        " << m.n[j] << ",\n";
        }
        out << "    }},\n";
        out << "    {{\n";
        for (int j = 0; j < m.len; j++) {
            out << "        " << m.m[j] << ",\n";
        }
        out << "    }},\n";
        out << "    {{\n";
        for (int j = 0; j < m.len; j++) {
            out << "        " << m.g[j] << ",\n";
        }
        out << "    }},\n";
        out << "    {{\n";
        for (int j = 0; j < m.len; j++) {
            out << "        " << m.h[j] << ",\n";
        }
        out << "    }},\n";
        out << "    {{\n";
        for (int j = 0; j < m.len; j++) {
            out << "        " << gScaled[static_cast<std::size_t>(j)] << ",\n";
        }
        out << "    }},\n";
        out << "    {{\n";
        for (int j = 0; j < m.len; j++) {
            out << "        " << hScaled[static_cast<std::size_t>(j)] << ",\n";
        }
        out << "    }}\n";
        out << "};\n\n";
    }

    out << "inline constexpr std::array<ModelView, " << models.size() << "> kModels = {\n";
    for (std::size_t i = 0; i < models.size(); i++) {
        out << "    ModelView{" << modelIdentifiers[i] << ".name, "
            << modelIdentifiers[i] << ".body, "
            << modelIdentifiers[i] << ".nmax, "
            << modelIdentifiers[i] << ".ndef, "
            << modelIdentifiers[i] << ".rscale, "
                << modelIdentifiers[i] << ".n.size(), "
                << modelIdentifiers[i] << ".n.data(), "
                << modelIdentifiers[i] << ".m.data(), "
                << modelIdentifiers[i] << ".g.data(), "
                    << modelIdentifiers[i] << ".h.data(), "
                    << modelIdentifiers[i] << ".g_scaled.data(), "
                    << modelIdentifiers[i] << ".h_scaled.data()},\n";
    }
    out << "};\n\n";

    out << "inline constexpr std::array<NameIndex, " << nameOrder.size() << "> kModelNameIndex = {\n";
    for (std::size_t idx : nameOrder) {
        out << "    NameIndex{\"" << models[idx].name << "\", " << idx << "},\n";
    }
    out << "};\n\n";

    out << "inline const ModelView *FindModel(std::string_view name) {\n";
    out << "    std::size_t lo = 0;\n";
    out << "    std::size_t hi = kModelNameIndex.size();\n";
    out << "    while (lo < hi) {\n";
    out << "        const std::size_t mid = lo + (hi - lo) / 2;\n";
    out << "        const auto key = kModelNameIndex[mid].name;\n";
    out << "        if (name < key) {\n";
    out << "            hi = mid;\n";
    out << "        } else if (key < name) {\n";
    out << "            lo = mid + 1;\n";
    out << "        } else {\n";
    out << "            return &kModels[kModelNameIndex[mid].index];\n";
    out << "        }\n";
    out << "    }\n";
    out << "    return nullptr;\n";
    out << "}\n\n";

    out << "} // namespace internalfield::models\n";
}

static void writeModelFunctionsSource(const std::vector<ModelData> &models, const fs::path &outputSource) {
    std::ofstream out(outputSource);
    if (!out.is_open()) {
        throw std::runtime_error("failed to open output file: " + outputSource.string());
    }

    out << "#include \"../src/models.h\"\n\n";
    out << "namespace internalfield::models {\n\n";

    for (const auto &model : models) {
        out << "Internal& " << model.name << "() {\n";
        out << "\tstatic Internal model(\"" << model.name << "\");\n";
        out << "\treturn model;\n";
        out << "}\n\n";
    }

    out << "/* map the model names to their model object pointers */\n";
    out << "const std::map<std::string,InternalFunc>& getModelPtrMap() {\n";
    out << "\tstatic std::map<std::string,InternalFunc> modelPtrMap = {\n";
    for (const auto &model : models) {
        out << "\t\t\t{\"" << model.name << "\"," << model.name << "},\n";
    }
    out << "\t};\n";
    out << "\treturn modelPtrMap;\n";
    out << "}\n\n";

    out << "InternalFunc getModelObjPointer(std::string Model) {\n";
    out << "\tconst auto& modelPtrMap = getModelPtrMap();\n";
    out << "\tauto it = modelPtrMap.find(Model);\n";
    out << "\treturn (it == modelPtrMap.end()) ? nullptr : it->second;\n";
    out << "}\n\n";

    out << "InternalFunc getModelObjPointer(const char *Model) {\n";
    out << "\tconst auto& modelPtrMap = getModelPtrMap();\n";
    out << "\tauto it = modelPtrMap.find(Model);\n";
    out << "\treturn (it == modelPtrMap.end()) ? nullptr : it->second;\n";
    out << "}\n\n";

    out << "std::vector<std::string> listAvailableModels() {\n";
    out << "\treturn listMapKeys(getModelPtrMap());\n";
    out << "}\n\n";

    out << "/* map of strings to direct field model function pointers */\n";
    out << "const std::map<std::string,modelFieldPtr>& getModelFieldPtrMap() {\n";
    out << "\tstatic std::map<std::string,modelFieldPtr> modelFieldPtrMap = {\n";
    for (const auto &model : models) {
        out << "\t\t\t{\"" << model.name << "\",&" << model.name << "Field},\n";
    }
    out << "\t};\n";
    out << "\treturn modelFieldPtrMap;\n";
    out << "}\n\n";

    out << "modelFieldPtr getModelFieldPtr(std::string Model) {\n";
    out << "\tconst auto& modelFieldPtrMap = getModelFieldPtrMap();\n";
    out << "\tauto it = modelFieldPtrMap.find(Model);\n";
    out << "\treturn (it == modelFieldPtrMap.end()) ? nullptr : it->second;\n";
    out << "}\n\n";

    out << "modelFieldPtr getModelFieldPtr(const char *Model) {\n";
    out << "\tconst auto& modelFieldPtrMap = getModelFieldPtrMap();\n";
    out << "\tauto it = modelFieldPtrMap.find(Model);\n";
    out << "\treturn (it == modelFieldPtrMap.end()) ? nullptr : it->second;\n";
    out << "}\n\n";

    out << "} // namespace internalfield::models\n\n";
    out << "using namespace internalfield;\n";
    out << "using namespace internalfield::models;\n\n";

    out << "extern \"C\" modelFieldPtr getModelFieldPtr(const char *Model) {\n";
    out << "\treturn internalfield::models::getModelFieldPtr(Model);\n";
    out << "}\n\n";

    for (const auto &model : models) {
        out << "void " << model.name << "Field(double x, double y, double z,\n";
        out << "\t\t\t\tdouble *bx, double *by, double *bz) {\n";
        out << "\tInternal model = " << model.name << "();\n";
        out << "\tmodel.FieldCart(x,y,z,bx,by,bz);\n";
        out << "}\n\n";
    }
}

static void writeModelListHeader(const std::vector<ModelData> &models, const fs::path &outputHeader) {
    std::ofstream out(outputHeader);
    if (!out.is_open()) {
        throw std::runtime_error("failed to open output file: " + outputHeader.string());
    }

    out << "#pragma once\n\n";
    out << "#define LIBINTERNALFIELD_MODEL_LIST(X) \\\n";
    for (std::size_t i = 0; i < models.size(); i++) {
        out << "    X(" << models[i].name << ")";
        if (i + 1 < models.size()) {
            out << " \\\n";
        } else {
            out << "\n";
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <coeff_dir> <output_header> [output_source] [output_model_list]\n";
        return 1;
    }

    const fs::path coeffDir = argv[1];
    const fs::path outputHeader = argv[2];
    const bool hasSourceOutput = argc >= 4;
    const fs::path outputSource = hasSourceOutput ? fs::path(argv[3]) : fs::path();
    const bool hasModelListOutput = argc >= 5;
    const fs::path outputModelList = hasModelListOutput ? fs::path(argv[4]) : fs::path();

    try {
        if (!fs::exists(coeffDir) || !fs::is_directory(coeffDir)) {
            std::cerr << "Coefficient directory does not exist: " << coeffDir << "\n";
            return 1;
        }

        refreshIgrfCoeffFiles(coeffDir);

        auto models = loadAllModels(coeffDir);
        if (models.empty()) {
            std::cerr << "No model files found in: " << coeffDir << "\n";
            return 1;
        }

        if (outputHeader.has_parent_path()) {
            fs::create_directories(outputHeader.parent_path());
        }

        writeRegistryHeader(models, outputHeader);

        if (hasSourceOutput) {
            if (outputSource.has_parent_path()) {
                fs::create_directories(outputSource.parent_path());
            }
            writeModelFunctionsSource(models, outputSource);
        }

        if (hasModelListOutput) {
            if (outputModelList.has_parent_path()) {
                fs::create_directories(outputModelList.parent_path());
            }
            writeModelListHeader(models, outputModelList);
        }

        std::cout << "Wrote registry for " << models.size() << " models to " << outputHeader << "\n";
        if (hasSourceOutput) {
            std::cout << "Wrote model functions for " << models.size() << " models to " << outputSource << "\n";
        }
        if (hasModelListOutput) {
            std::cout << "Wrote model list for " << models.size() << " models to " << outputModelList << "\n";
        }
        return 0;
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
}
