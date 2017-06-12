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
	void tauA_computation(vector<Pair> &input, int n);

	void naive_algorithm(vector<Pair> &input, int num_threads);

	void set_tauA(int tauA);
	double get_tauA();

private:
	double tauA;
};

#endif //NAIVE_H