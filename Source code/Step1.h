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
};

