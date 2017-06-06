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
	#pragma omp parallel for
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			num += Naive::calc_sign(input[i], input[j]);
	double result = (double) num / (n*(n - 1) / 2);
	return result;
}

void Naive::calculate_tau_a(vector<vector<double>> &dataset, int num_threads) {

#ifdef _OPENMP
	/* Set the number of threads */
	omp_set_num_threads(num_threads);
#endif

	double overall_start_clock = omp_get_wtime();
	
	vector<Pair> elements;
	for (int i = 0; i < dataset.size(); i++) {
		vector<double> u = dataset[i];
		for (int j = i + 1; j < dataset.size(); j++) {
			vector<double> v = dataset[j];
			for (int k = 0; k < dataset[i].size(); k++) {
				elements.insert(elements.end(), Pair(u[i], v[i]));
			}

			int n = elements.size();

			double tau_a = Naive::kendall_tau_a_naive(elements, n);
			cout << "Kendall's tauA coefficient: " << tau_a << endl;
		}
	}
	
	double overall_end_clock = omp_get_wtime();
	cout << "Overall time: " << overall_end_clock - overall_start_clock << endl;
	cout << endl;

	system("pause");
}