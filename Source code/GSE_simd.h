#pragma once

#include "Pair.h"
#include <vector>
#include <omp.h>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

class GSE_simd
{
public:
	GSE_simd();
	~GSE_simd();

	int step1_partition(vector<Pair> &elements, int p, int r);
	int step1_compare_elements(Pair pLeft, Pair pRight);
	void step1_quicksort(vector<Pair> &elements, int p, int r);

	void step2_scan(vector<Pair> &elements);

	int step3_merge(vector<Pair> &in, vector<Pair> &buffer, int left, int mid, int right);
	void step3_divide(vector<Pair> &pairs, int n);

	void step4_scan(vector<Pair> &elements);

	void step5_tauB_computation(int n, double n1, double n2, double n3, int nd);

	void GSE_algorithm(vector<Pair> &input, int num_threads);

	void set_n1(double n1);
	double get_n1();

	void set_n2(double n2);
	double get_n2();

	void set_n3(double n3);
	double get_n3();

	void set_nd(int nd);
	int get_nd();

	void set_tauB(double tauB);
	double get_tauB();

private:
	double n1, n2, n3, tauB;
	int nd;
};
