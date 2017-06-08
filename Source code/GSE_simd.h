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

	void swap_elements(vector<Pair> &elements, int pLeft, int pRight);

	int compare_elements(Pair pLeft, Pair pRight);

	void quicksort(vector<Pair> &elements, int left, int right);

	void scan(vector<Pair> &elements, int control);

	int divide(vector<Pair> &pairs, vector<Pair> &buffer, int n);

	int merge(vector<Pair> &in, vector<Pair> &out, int left, int mid, int right);

	double tauB_computation(int n, double n1, double n2, double n3, int nd);

	void calculate_tau_b(vector<Pair> &input);

	void setN1(double n);
	double getN1();

	void setN2(double n);
	double getN2();

	void setN3(double n);
	double getN3();

	void setNd(int n);
	int getNd();

private:
	double n1, n2, n3;
	int nd;
};
