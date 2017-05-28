#include "Step3.h"

Step3::Step3()
{
}

Step3::~Step3()
{
}


int Step3::step3_merge(vector<Pair> &in, vector<Pair> &out, int left, int mid, int right) {
	int l = left;
	int p = left;
	int r = mid;
	int nd = 0;
	while (l < mid && r < right) {
		if (in[r].getSecond() < in[l].getSecond()) {
			nd += mid - l;
			out[p++] = in[r++];
		}
		else
			out[p++] = in[l++];
	}
	while (l < mid) 
		out[p++] = in[l++];
	while (r < right) {
		nd += mid - l;
		out[p++] = in[r++];
	}
	return nd;
}

int Step3::step3_divide(vector<Pair> &input, vector<Pair> &buffer, int n) {
	vector<Pair> in = input;
	vector<Pair> out = buffer;
	int nd = 0;
	for (int s = 1; s < n; s *= 2) {
		for (int l = 0; l < n; l += 2 * s) {
			int m = min(l + s, n);
			int r = min(l + 2 * s, n);
			nd += Step3::step3_merge(in, out, l, m, r);
		}
	swap(in, out);
	}
	input = in;
	return nd;
}

/*int main()
{
	Step3 step3;
	vector<Pair> input = { Pair(1, 2), Pair(2, 2), Pair(2, 3), Pair(3, 1) };
	int n = input.size();
	for (int i = 0; i < n; i++) {
		cout << "(" << input[i].getFirst() << "," << input[i].getSecond() << ") ";
	}
	cout << endl;
	vector<Pair> buffer = input;
	int nd = step3.step3_divide(input, buffer, n);
	for (int i = 0; i < n; i++) {
		cout << "(" << input[i].getFirst() << "," << input[i].getSecond() << ") ";
	}
	cout << endl;
	cout << nd << endl;
	system("pause");
	return 0;
}*/