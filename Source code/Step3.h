#pragma once
#include <vector>

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