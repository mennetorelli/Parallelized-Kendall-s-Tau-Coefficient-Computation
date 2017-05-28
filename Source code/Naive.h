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
	double kendall_tau_a_naive(vector<Pair> &input, int n);

	void calculate_tau_a(vector<Pair> &input, Naive naive);
};

#endif //NAIVE_H