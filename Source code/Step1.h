#pragma once

#include "Pair.h"
#include <vector>

using namespace std;

class Step1
{
public:
	Step1();
	~Step1();

	void swap_elements(vector<Pair> &elements, int pLeft, int pRight);

	int compare_elements(Pair pLeft, Pair pRight);

	void quicksort(vector<Pair> &elements, int left, int right);

	void scan(vector<Pair> &elements, int control);

	void setN1(double n);
	double getN1();

	void setN2(double n);
	double getN2();

	void setN3(double n);
	double getN3();

private:
	double n1, n2, n3;

};

