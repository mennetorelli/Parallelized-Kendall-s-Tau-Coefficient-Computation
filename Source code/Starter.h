#pragma once

#include "Pair.h"
#include "Naive.h"
#include "GSE.h"
#include <vector>
#include <omp.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <ctime>
#include <iostream>
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
	vector<vector<int>> Starter::parse_dataset(string filename);
};

