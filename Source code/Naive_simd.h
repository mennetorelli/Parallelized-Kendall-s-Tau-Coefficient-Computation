#pragma once

#include "Pair.h"
#include "Pair.h"
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef NAIVE_SIMD_H
#define NAIVE_SIMD_H

using namespace std;

class Naive_simd
{
public:
	Naive_simd();
	~Naive_simd();

	int calc_sign(int v);
	void tauA_computation(vector<int> &u, vector<int> &v, int n);

	void naive_algorithm(vector<int> &u, vector<int> &v, int n, int num_threads);

private:
	double tauA;
};

#endif //NAIVE_SIMD_H