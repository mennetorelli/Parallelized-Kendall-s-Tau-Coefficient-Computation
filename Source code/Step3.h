#pragma once

#include "Pair.h"
#include "Pair.h"
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef STEP3_H
#define STEP3_H

class Step3
{
public:
	Step3();
	~Step3();

	int step3_divide(vector<Pair> pairs, vector<Pair> buffer, int n);
	int step3_merge(vector<Pair> in, vector<Pair> out, int left, int mid, int right);
	
private:
	int nd;
};

#endif //STEP3_H