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
	int num = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			num += Naive::calc_sign(input[i], input[j]);
	double result = (double) num / (n*(n - 1) / 2);
	return result;
}

void Naive::calculate_tau_a(vector<Pair> &input) {
	double overall_start_clock = omp_get_wtime();
	
	int n = input.size();
	
	double tau_a = Naive::kendall_tau_a_naive(input, n);
	cout << "Kendall's tauB coefficient: " << tau_a << endl;
	
	double overall_end_clock = omp_get_wtime();
	cout << "Overall time: " << overall_end_clock - overall_start_clock << endl;
	cout << endl;

	system("pause");
}