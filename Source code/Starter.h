#pragma once

#include "Pair.h"
#include "Naive.h"
#include "GSE.h"
#include "GSE_simd.h"
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
	void read_input_file(vector<Pair> &elements);
};

