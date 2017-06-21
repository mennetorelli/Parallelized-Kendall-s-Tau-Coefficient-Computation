#include "GSE.h"

GSE::GSE()
{
	GSE::n1 = 0;
	GSE::n2 = 0;
	GSE::n3 = 0;
	GSE::tauB = 0;
}

GSE::~GSE()
{
}


/**
  Compares first and second element in a pair
*/
int GSE::step1_compare_elements(Pair pLeft, Pair pRight) {

	int result = 0;

	if (pLeft.getFirst() > pRight.getFirst())
		result = 1;
	if (pLeft.getFirst() < pRight.getFirst())
		result = -1;

	if (result == 0) {
		if (pLeft.getSecond() > pRight.getSecond())
			result = 1;
		if (pLeft.getSecond() < pRight.getSecond())
			result = -1;
	}

	return result;
}

/**
  Partition step of quicksort
*/
int GSE::step1_partition(vector<Pair> &elements, int p, int r) {
	Pair pivot = elements[r];
	int i = p - 1;

	for (int j = p; j < r; j++) {
		if (step1_compare_elements(elements[j], pivot)!=1) {
			// Move wall one index to the right
			i++;
			// Move current element to the left of the wall
			Pair temp = elements[i];
			elements[i] = elements[j];
			elements[j] = temp;
		}
	}

	// Put pivot element to the left of larger elements
	Pair temp = elements[i + 1];
	elements[i + 1] = elements[r];
	elements[r] = temp;

	return i + 1;
}

/**
  Quicksort algorithm
*/
void GSE::step1_quicksort(vector<Pair> &elements, int p, int r) {
	int q;

	if (p < r) {
		q = step1_partition(elements, p, r);

		#pragma omp parallel sections
		{
			#pragma omp section
			step1_quicksort(elements, p, q - 1);

			#pragma omp section
			step1_quicksort(elements, q + 1, r);
		}
	}
}

/**
  Scans the vector of pairs sorted by the first element (and in case of equality, by the second) 
  to compute n1 and n3
*/
void GSE::step2_scan(vector<Pair> &elements) {
	int ni = 1;
	int wi = 1;

	for (int i = 1; i < elements.size(); i++) {
		// Counts the quantity of tied first elements in each group
		if (elements[i].getFirst() == elements[i - 1].getFirst()) {
			ni++;

			// Counts the tied couples
			if (elements[i].getSecond() == elements[i - 1].getSecond() &&
				elements[i - 1].getFirst() == elements[i - 1].getSecond())
				wi++;
			// Sets the parameters and restarts the counters
			else {
				GSE::n3 += (double) wi * (wi - 1) / 2;
				wi = 1;
			}
		}

		// Sets the parameters and restarts the counters
		else {
			GSE::n1 += (double) ni * (ni - 1) / 2;
			GSE::n3 += (double) wi * (wi - 1) / 2;
			ni = 1;
			wi = 1;
		}
	}

	GSE::n1 += (double) ni * (ni - 1) / 2;
	GSE::n3 += (double) wi * (wi - 1) / 2;
}

/**
  Scans the vector of pairs sorted by the second element to compute n2
*/
void GSE::step4_scan(vector<Pair> &elements) {
	int ni = 1;

	// counts the quantity of tied second elements in each group
	for (int i = 1; i < elements.size(); i++) {
		if (elements[i].getSecond() == elements[i - 1].getSecond()) ni++;

		// sets the parameters and restarts the counters
		else {
			GSE::n2 += (double) ni * (ni - 1) / 2;
			ni = 1;
		}
	}

	GSE::n2 += (double) ni * (ni - 1) / 2;
}

/**
  Merges the sorted subvectors
*/
int GSE::step3_merge(vector<Pair> &input, vector<Pair> &buffer, int left, int mid, int right) {
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

/**
  Bottom-up mergesort implementation
*/
void GSE::step3_divide(vector<Pair> &input, int n) {
	vector<Pair> buffer = input;
	int nd = 0;
	#pragma omp parallel reduction(+:nd) 
	{
		for (int s = 1; s < n; s *= 2) {
			#pragma omp for
			for (int l = 0; l < n; l += 2 * s) {
				int m = min(l + s, n);
				int r = min(l + 2 * s, n);
				nd += GSE::step3_merge(input, buffer, l, m, r);
			}
			#pragma omp master
			swap(input, buffer);
			#pragma omp barrier
		}
	}
	GSE::nd = nd;
}

/**
  Computes the value of TauB
*/
void GSE::step5_tauB_computation(int n, double n1, double n2, double n3, int nd) {
	double result;

	double n0 = (double) n * (n - 1) / 2;
	
	double num = n0 - n1 - n2 + n3 - 2 * nd;
	double den = sqrt((n0 - n1) * (n0 - n2));

	result = (double) num / den;

	GSE::tauB = result;
}

/**
  Manages the steps of the algorithm
*/
void GSE::GSE_algorithm(vector<int> &u, vector<int> &v, int n, int num_threads) {

#ifdef _OPENMP
	// Set the number of threads
	omp_set_num_threads(num_threads);
	// Enable nested parallelism
	omp_set_nested(1);
	//omp_set_max_active_levels(num_threads);
#endif

	vector<Pair> elements;
	for (int i = 0; i < n; i++) {
		elements.insert(elements.end(), Pair(u[i], v[i]));
	}

	double overall_start_clock = omp_get_wtime();

	double step1_start_clock = omp_get_wtime();
	GSE::step1_quicksort(elements, 0, n - 1);
	double step1_end_clock = omp_get_wtime();

	GSE::step2_scan(elements);

	double step3_start_clock = omp_get_wtime();
	GSE::step3_divide(elements, n);
	double step3_end_clock = omp_get_wtime();

	GSE::step4_scan(elements);

	GSE::step5_tauB_computation(n, GSE::n1, GSE::n2, GSE::n3, GSE::nd);

	cout << "n1: " << GSE::n1 << ", " << "n2: " << GSE::n2 << ", " 
		<< "n3: " << GSE::n3 << ", " << "nd: " << GSE::nd << endl;
	
	cout << "Kendall's tauB coefficient: " << GSE::tauB << endl;

	double overall_end_clock = omp_get_wtime();

	cout << endl;
	cout << "Time for Step1:" << step1_end_clock - step1_start_clock << endl;
	cout << "Time for Step3:" << step3_end_clock - step3_start_clock << endl;
	cout << "Overall time:" << overall_end_clock - overall_start_clock << endl;
	cout << endl;

	system("pause");
}
