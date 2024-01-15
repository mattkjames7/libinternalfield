#ifndef __TIMER_H__
#define __TIMER_H__
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <internalfield.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>

#endif

typedef std::tuple<
    std::vector<double>,
    std::vector<double>,
    std::vector<double>,
    std::vector<double>,
    std::vector<double>,
    std::vector<double>
    > vectorTuple;



typedef struct {
    double muPolarSingle;
    double sdPolarSingle;
    double muPolarArray;
    double sdPolarArray;
    double muCartSingle;
    double sdCartSingle;
    double muCartArray;
    double sdCartArray;
} timingResult;


void test(int n, double *mu_vp, double *mu_sp, double *mu_vc, double *mu_sc);
