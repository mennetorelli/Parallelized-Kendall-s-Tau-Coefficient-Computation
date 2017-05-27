#include "Step3.h"
#include "Pair.h"
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int step3_divide(vector<Pair> pairs, vector<Pair> buffer, int n) {
	vector<Pair> in = pairs;
	vector<Pair> out = buffer;
	int nd = 0;
	for (int s=0; s<n; s*=2) {
		for (int l = 0; l<n; l = 2*s) {
			int m = min(l + s, n);
			int r = min(l + 2 * s, n);
			nd += step3_merge(in, out, l, m, r);
		}
	swap(in, out);
	}
	if (pairs != in)
		memcpy(pairs, in, n * sizeof(pairs));
	return nd;
}

int step3_merge(vector<Pair> in, vector<Pair> out, int left, int mid, int right) {
	int l = left;
	int p = left;
	int r = mid;
	int nd = 0;
	while (l < mid && r < right) {
		if (in[r].getSecond < in[l].getSecond) {
			nd = nd + mid - l;
			out[p++] = in[r++];
		}
		else
			out[p++] = in[l++];
	}
	return nd;
}



int main()
{
	#pragma omp parallel num_threads(3)
	{
		cout << "Hello World" << endl;
	}
	return 0;
}