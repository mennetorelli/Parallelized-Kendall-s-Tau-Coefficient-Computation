#include "Naive.h"

Naive::Naive()
{
	set_tauA(0);
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

void Naive::tauA_computation(vector<Pair> &input, int n) {
	int num = 0;
	#pragma omp parallel for reduction(+:num)
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			num += Naive::calc_sign(input[i], input[j]);
	double result = (double) num / (n*(n - 1) / 2);
	Naive::set_tauA(result);
}

void Naive::naive_algorithm(vector<Pair> &input, int num_threads) {

#ifdef _OPENMP
	/* Set the number of threads */
	omp_set_num_threads(num_threads);
#endif

	double overall_start_clock = omp_get_wtime();
	
	int n = input.size();
	
	Naive::tauA_computation(input, n);
	cout << "Kendall's tauA coefficient: " << Naive::tauA << endl;
	
	double overall_end_clock = omp_get_wtime();
	cout << "Overall time: " << overall_end_clock - overall_start_clock << endl;
	cout << endl;

	system("pause");
}

void Naive::set_tauA(int tauA) {
	Naive::tauA = tauA;
}

double Naive::get_tauA() {
	return Naive::tauA;
}