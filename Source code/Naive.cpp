#include "Naive.h"

Naive::Naive()
{
}

Naive::~Naive()
{
}


int Naive::calc_sign(Pair pair1, Pair pair2) {
	if ((pair1.getFirst() - pair2.getFirst()) * (pair1.getSecond() - pair2.getSecond()) > 0)
		return 1;
	if ((pair1.getFirst() - pair2.getFirst()) * (pair1.getSecond() - pair2.getSecond()) < 0)
		return -1;
	if ((pair1.getFirst() - pair2.getFirst()) * (pair1.getSecond() - pair2.getSecond()) == 0)
		return 0;
}

double Naive::kendall_tau_a_naive(vector<Pair> &input, int n) {
	int numerator = 0;
	for (int i = 0; i < n; i++)
		for (int j = 1; j < n - 1; j++)
			numerator += Naive::calc_sign(input[i], input[j]);
	return double(numerator) / (n * (n - 1) / 2);
}


void Naive::calculate_tau_a(vector<Pair> &input) {
	int n = input.size();
	for (int i = 0; i < n; i++) {
		cout << "(" << input[i].getFirst() << "," << input[i].getSecond() << ") ";
	}
	cout << endl;
	double tau_a = Naive::kendall_tau_a_naive(input, n);
	cout << tau_a << endl;
	system("pause");
}