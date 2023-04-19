#ifndef __TEST_H__
#define __TEST_H__
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <array>
#include <internalfield.h>
#include "testdata.h"
#include <tuple>
#include <sstream>

typedef std::tuple<
    std::vector<double>,
    std::vector<double>,
    std::vector<double>
    > FieldVectors;


#endif
