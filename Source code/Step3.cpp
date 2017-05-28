#include "Step3.h"

Step3::Step3()
{
}

Step3::~Step3()
{
}


int Step3::step3_merge(vector<Pair> &input, vector<Pair> &buffer, int left, int mid, int right) {
	int l = left;
	int p = left;
	int r = mid;
	int nd = 0;
	while (l < mid && r < right) {
		if (input[r].getSecond() < input[l].getSecond()) {
			nd += mid - l;
			buffer[p++] = input[r++];
		}
		else
			buffer[p++] = input[l++];
	}
	while (l < mid)
		buffer[p++] = input[l++];
	while (r < right) {
		nd += mid - l;
		buffer[p++] = input[r++];
	}
	return nd;
}

int Step3::step3_divide(vector<Pair> &input, vector<Pair> &buffer, int n) {
	int nd = 0;
	for (int s = 1; s < n; s *= 2) {
		for (int l = 0; l < n; l += 2 * s) {
			int m = min(l + s, n);
			int r = min(l + 2 * s, n);
			nd += Step3::step3_merge(input, buffer, l, m, r);
		}
	swap(input, buffer);
	}
	return nd;
}

int main()
{
	Step3 step3;
	vector<Pair> input = { Pair(1, 2), Pair(1, 3), Pair(2, 1), Pair(2, 2), Pair(2, 3), Pair(2, 4),  Pair(4, 1), Pair(4, 4) };
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
}