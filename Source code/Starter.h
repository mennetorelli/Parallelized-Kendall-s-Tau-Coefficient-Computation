#pragma once

#include "Pair.h"
#include "Naive.h"
#include "GSE.h"
#include "GSE_simd.h"
#include "Naive_simd.h"
#include <vector>
#include <omp.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Starter
{
public:
	Starter();
	~Starter();

	void init();
	void generate_input_file();
	int read_input_file(vector<vector<int>> &elements, vector<int> &u, vector<int> &v);
};

