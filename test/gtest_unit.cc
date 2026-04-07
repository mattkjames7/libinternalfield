#define _USE_MATH_DEFINES
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <tuple>
#include <vector>

#include <internalfield.h>

#include "testdata.h"

using FieldVectors = std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>;

static FieldVectors getPositions() {
    std::vector<double> r = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    std::vector<double> tdeg = {10, 10, 10, 10, 55, 55, 55, 55, 90, 90, 90, 90, 130, 130, 130, 130};
    std::vector<double> pdeg = {0, 27, 180, 340, 0, 27, 180, 340, 0, 27, 180, 340, 0, 27, 180, 340};
    std::vector<double> t(16);
    std::vector<double> p(16);

    const double deg2rad = M_PI / 180.0;
    for (std::size_t i = 0; i < t.size(); i++) {
        t[i] = deg2rad * tdeg[i];
        p[i] = deg2rad * pdeg[i];
    }

    return {r, t, p};
}

static FieldVectors getPositionsCart() {
    FieldVectors pos = getPositions();

    std::vector<double> r = std::get<0>(pos);
    std::vector<double> t = std::get<1>(pos);
    std::vector<double> p = std::get<2>(pos);

    const std::size_t n = r.size();
    std::vector<double> x(n), y(n), z(n);
    for (std::size_t i = 0; i < n; i++) {
        x[i] = r[i] * std::cos(t[i]) * std::cos(p[i]);
        y[i] = r[i] * std::cos(t[i]) * std::sin(p[i]);
        z[i] = r[i] * std::sin(t[i]);
    }
    return {x, y, z};
}

static FieldVectors vip4Vectors(const FieldVectors &pos) {
    std::vector<double> r = std::get<0>(pos);
    std::vector<double> t = std::get<1>(pos);
    std::vector<double> p = std::get<2>(pos);

    std::vector<double> Br(r.size());
    std::vector<double> Bt(t.size());
    std::vector<double> Bp(p.size());

    InternalModel internalModel = getInternalModel();
    internalModel.SetModel("vip4");
    internalModel.SetCartIn(false);
    internalModel.SetCartOut(false);

    internalModel.Field(static_cast<int>(r.size()), r.data(), t.data(), p.data(), Br.data(), Bt.data(), Bp.data());

    return {Br, Bt, Bp};
}

static FieldVectors jrm09Vectors(const FieldVectors &pos) {
    std::vector<double> r = std::get<0>(pos);
    std::vector<double> t = std::get<1>(pos);
    std::vector<double> p = std::get<2>(pos);

    std::vector<double> Br(r.size());
    std::vector<double> Bt(t.size());
    std::vector<double> Bp(p.size());

    InternalModel internalModel = getInternalModel();
    internalModel.SetModel("jrm09");
    internalModel.SetCartIn(false);
    internalModel.SetCartOut(false);

    internalModel.Field(static_cast<int>(r.size()), r.data(), t.data(), p.data(), Br.data(), Bt.data(), Bp.data());

    return {Br, Bt, Bp};
}

static FieldVectors vip4FunctionVectors(const FieldVectors &pos) {
    std::vector<double> x = std::get<0>(pos);
    std::vector<double> y = std::get<1>(pos);
    std::vector<double> z = std::get<2>(pos);

    std::vector<double> Bx(x.size());
    std::vector<double> By(x.size());
    std::vector<double> Bz(x.size());

    for (std::size_t i = 0; i < x.size(); i++) {
        vip4Field(x[i], y[i], z[i], &Bx[i], &By[i], &Bz[i]);
    }
    return {Bx, By, Bz};
}

static FieldVectors readTestVectors(const std::string &file) {
    std::vector<double> tr, tt, tp, tbr, tbt, tbp;
    std::filesystem::path path = file;
    readVectors(path, tr, tt, tp, tbr, tbt, tbp);
    return {tbr, tbt, tbp};
}

static bool compareSavedVectors(const FieldVectors &origField, const FieldVectors &bField) {
    return compareVectors(
        std::get<0>(bField), std::get<1>(bField), std::get<2>(bField),
        std::get<0>(origField), std::get<1>(origField), std::get<2>(origField));
}

TEST(InternalFieldUnit, Vip4ReferenceVectorsMatch) {
    FieldVectors pos = getPositions();
    FieldVectors bVip4 = vip4Vectors(pos);
    FieldVectors origVip4 = readTestVectors("data/testvip4.bin");

    EXPECT_TRUE(compareSavedVectors(origVip4, bVip4));
}

TEST(InternalFieldUnit, Jrm09ReferenceVectorsMatch) {
    FieldVectors pos = getPositions();
    FieldVectors bJrm09 = jrm09Vectors(pos);
    FieldVectors origJrm09 = readTestVectors("data/testjrm09.bin");

    EXPECT_TRUE(compareSavedVectors(origJrm09, bJrm09));
}

TEST(InternalFieldUnit, Vip4FunctionReferenceVectorsMatch) {
    FieldVectors pos = getPositionsCart();
    FieldVectors bVip4 = vip4FunctionVectors(pos);
    FieldVectors origVip4 = readTestVectors("data/testvip4function.bin");

    EXPECT_TRUE(compareSavedVectors(origVip4, bVip4));
}

TEST(InternalFieldUnit, ModelVariablesMatchFixture) {
    std::vector<std::vector<double>> Snm0, Snm1, g0, g1, h0, h1;
    std::vector<internalfield::schmidtcoeffs> schc0, schc1;

    Internal model("vip4");
    schc1 = model.getSchmidtCoeffs();
    Snm1 = model.getSnm();
    g1 = model.getg();
    h1 = model.geth();

    std::filesystem::path file = std::filesystem::current_path() / "data/testmodelvars.bin";
    readModelVariables(file, schc0, Snm0, g0, h0);

    ASSERT_EQ(schc0.size(), schc1.size());
    for (std::size_t i = 0; i < schc0.size(); i++) {
        EXPECT_EQ(schc0[i].n, schc1[i].n);
        EXPECT_EQ(schc0[i].m, schc1[i].m);
        EXPECT_EQ(schc0[i].g, schc1[i].g);
        EXPECT_EQ(schc0[i].h, schc1[i].h);
    }

    EXPECT_EQ(Snm0, Snm1);
    EXPECT_EQ(g0, g1);
    EXPECT_EQ(h0, h1);
}

TEST(InternalFieldUnit, Vip4MacroWrapperProducesValidAndConsistentOutput) {
    const double x = 9.5;
    const double y = -2.25;
    const double z = 1.75;

    double bxWrap = 0.0;
    double byWrap = 0.0;
    double bzWrap = 0.0;
    vip4Field(x, y, z, &bxWrap, &byWrap, &bzWrap);

    InternalModel model;
    model.SetModel("vip4");
    model.SetCartIn(true);
    model.SetCartOut(true);

    double bxModel = 0.0;
    double byModel = 0.0;
    double bzModel = 0.0;
    model.Field(x, y, z, &bxModel, &byModel, &bzModel);

    EXPECT_TRUE(std::isfinite(bxWrap));
    EXPECT_TRUE(std::isfinite(byWrap));
    EXPECT_TRUE(std::isfinite(bzWrap));

    const double absTol = 1e-6;
    EXPECT_LE(std::fabs(bxWrap - bxModel), absTol);
    EXPECT_LE(std::fabs(byWrap - byModel), absTol);
    EXPECT_LE(std::fabs(bzWrap - bzModel), absTol);
}

TEST(InternalFieldUnit, SingletonConfigRoundTripAndFieldChange) {
    double x = 8.0;
    double y = 1.25;
    double z = -0.5;

    char modelName[64];
    bool cartIn = false;
    bool cartOut = false;
    int maxDeg = 0;

    SetInternalCFG("vip4", true, true, 1);
    GetInternalCFG(modelName, &cartIn, &cartOut, &maxDeg);

    EXPECT_STREQ(modelName, "vip4");
    EXPECT_TRUE(cartIn);
    EXPECT_TRUE(cartOut);
    EXPECT_EQ(maxDeg, 1);

    double bxA = 0.0;
    double byA = 0.0;
    double bzA = 0.0;
    InternalField(1, &x, &y, &z, &bxA, &byA, &bzA);

    SetInternalCFG("vip4", true, true, 4);
    GetInternalCFG(modelName, &cartIn, &cartOut, &maxDeg);

    EXPECT_STREQ(modelName, "vip4");
    EXPECT_TRUE(cartIn);
    EXPECT_TRUE(cartOut);
    EXPECT_EQ(maxDeg, 4);

    double bxB = 0.0;
    double byB = 0.0;
    double bzB = 0.0;
    InternalField(1, &x, &y, &z, &bxB, &byB, &bzB);

    EXPECT_TRUE(std::isfinite(bxA));
    EXPECT_TRUE(std::isfinite(byA));
    EXPECT_TRUE(std::isfinite(bzA));
    EXPECT_TRUE(std::isfinite(bxB));
    EXPECT_TRUE(std::isfinite(byB));
    EXPECT_TRUE(std::isfinite(bzB));

    const double delta = std::fabs(bxA - bxB) + std::fabs(byA - byB) + std::fabs(bzA - bzB);
    EXPECT_GT(delta, 1e-6);
}
