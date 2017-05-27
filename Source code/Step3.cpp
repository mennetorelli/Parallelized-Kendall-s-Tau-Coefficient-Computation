#include "Step3.h"
#include "Pair.h"
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Step3::step3_divide(vector<Pair> in, vector<Pair> out, int n) {
	int nd = 0;
	for (int s=0; s<n; s*=2) {
		for (int l = 0; l<n; l = 2*s) {
			int m = min(l + s, n);
			int r = min(l + 2 * s, n);
			nd += step3_merge(in, out, l, m, r);
		}
	swap(in, out);
	}
	return nd;
}

int Step3::step3_merge(vector<Pair> in, vector<Pair> out, int left, int mid, int right) {
	int l = left;
	int p = left;
	int r = mid;
	int nd = 0;
	while (l < mid && r < right) {
		if (in[r].getSecond() < in[l].getSecond()) {
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
	vector<Pair> input = { Pair(1, 2), Pair(2, 3), Pair(2, 2), Pair(3, 1) };
	int n = input.size();
	cout << n << endl;
	int prova = Step3::step3_divide(input, input, n);
	cout << prova << endl;
	return 0;
}