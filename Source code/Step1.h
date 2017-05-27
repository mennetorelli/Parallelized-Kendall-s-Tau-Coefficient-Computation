#pragma once

#include <vector>
#include "Pair.h"

class Step1
{
public:
	Step1();
	~Step1();

	void swap_elements(std::vector<Pair> &elements, int pLeft, int pRight);

	int compare_elements(Pair pLeft, Pair pRight);

	void quicksort(std::vector<Pair> &elements, int left, int right);
};

