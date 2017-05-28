#pragma once

#include "Pair.h"
#include "Pair.h"
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef NAIVE_H
#define NAIVE_H

using namespace std;

class Naive
{
public:
	Naive();
	~Naive();

	int calc_sign(Pair pair1, Pair pair2);
	double Naive::kendall_tau_a_naive(vector<Pair> &input, int n);
};

#endif //NAIVE_H