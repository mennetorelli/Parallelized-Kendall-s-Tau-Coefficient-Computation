#pragma once

class Step3
{
public:
	Step3();
	~Step3();

	int step3_divide(Pair pairs[], Pair buffer[], int n);
	int step3_merge(Pair in[], Pair out[], int left, int mid, int right);
	
private:
	int nd;
};