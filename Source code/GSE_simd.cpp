#include "GSE_simd.h"

GSE_simd::GSE_simd()
{
	setN1(0);
	setN2(0);
	setN3(0);
	setNd(0);
}

GSE_simd::~GSE_simd()
{
}

void GSE_simd::swap_elements(vector<Pair> &elements, int pLeft, int pRight) {

	Pair tmp = elements[pRight];
	elements[pRight] = elements[pLeft];
	elements[pLeft] = tmp;
}

int GSE_simd::compare_elements(Pair pLeft, Pair pRight) {

	int result = 0;

	if (pLeft.getFirst() > pRight.getFirst()) result = 1;
	if (pLeft.getFirst() < pRight.getFirst()) result = -1;

	if (result == 0) {
		if (pLeft.getSecond() > pRight.getSecond()) result = 1;
		if (pLeft.getSecond() < pRight.getSecond()) result = -1;
	}

	return result;
}

void GSE_simd::quicksort(vector<Pair> &elements, int left, int right) {

	Pair p = elements[(left + right) / 2];
	int l = left, r = right;

	while (l <= r)
	{
		while (compare_elements(elements[l], p) < 0) l++;
		while (compare_elements(elements[r], p) > 0) r--;

		if (l <= r)
		{
			swap_elements(elements, l, r);
			l++;
			r--;
		}
	}

		if (left < r) quicksort(elements, left, r);

		if (l < right) quicksort(elements, l, right);
}

void GSE_simd::scan(vector<Pair> &elements, int control) {

	if (control != 1 && control != 2) {
		cout << "Scan function can take only 1 or 2 as control input" << endl;
		return;
	}

	if (control == 1) {
		int Ni = 1;
		int Wi = 1;
	
		//#pragma omp simd
		for (int i = 1; i < elements.size(); i++) {
			if (elements[i].getFirst() == elements[i - 1].getFirst()) {
				Ni++;

				if (elements[i].getSecond() == elements[i - 1].getSecond() &&
					elements[i - 1].getFirst() == elements[i - 1].getSecond()) Wi++;
				else {
					setN3(getN3() + (double)Wi*(Wi - 1) / 2);
					Wi = 1;
				}
			}

			else {

				setN1(getN1() + (double)Ni*(Ni - 1) / 2);
				setN3(getN3() + (double)Wi*(Wi - 1) / 2);
				Ni = 1;
				Wi = 1;
			}
		}

		setN1(getN1() + (double)Ni*(Ni - 1) / 2);
		setN3(getN3() + (double)Wi*(Wi - 1) / 2);
	}


	if (control == 2) {
		int Ni = 1;
		double N2 = 0;

		//#pragma omp simd
		for (int i = 1; i < elements.size(); i++) {
			if (elements[i].getSecond() == elements[i - 1].getSecond()) Ni++;

			else {
				setN2(getN2() + (double)Ni*(Ni - 1) / 2);
				Ni = 1;
			}
		}

		setN2(getN2() + (double)Ni*(Ni - 1) / 2);
	}

}

int GSE_simd::merge(vector<Pair> &input, vector<Pair> &buffer, int left, int mid, int right) {
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

int GSE_simd::divide(vector<Pair> &input, vector<Pair> &buffer, int n) {
	int nd = 0; 
	
		for (int s = 1; s < n; s *= 2) {
			//#pragma omp simd
			for (int l = 0; l < n; l += 2 * s) {
				int m = min(l + s, n);
				int r = min(l + 2 * s, n);
				nd += GSE_simd::merge(input, buffer, l, m, r);
			}

			swap(input, buffer);

		}
	
	return nd;
}

double GSE_simd::tauB_computation(int n, double n1, double n2, double n3, int nd) {
	double result;

	double n0 = (double)n*(n - 1) / 2;

	double num = n0 - n1 - n2 + n3 - 2 * nd;
	double den = sqrt((n0 - n1)*(n0 - n2));

	result = (double)num / den;

	return result;
}

void GSE_simd::calculate_tau_b(vector<Pair> &input) {


	double overall_start_clock = omp_get_wtime();

	int n = input.size();

	double step1_start_clock = omp_get_wtime();
	GSE_simd::quicksort(input, 0, n - 1);
	double step1_end_clock = omp_get_wtime();

	double step2_start_clock = omp_get_wtime();
	GSE_simd::scan(input, 1);
	double step2_end_clock = omp_get_wtime();

	double step3_start_clock = omp_get_wtime();
	vector<Pair> buffer = input;
	GSE_simd::setNd(GSE_simd::divide(input, buffer, n));
	double step3_end_clock = omp_get_wtime();

	double step4_start_clock = omp_get_wtime();
	GSE_simd::scan(input, 2);
	double step4_end_clock = omp_get_wtime();

	cout << "N1:" << GSE_simd::getN1() << endl;
	cout << "N2:" << GSE_simd::getN2() << endl;
	cout << "N3:" << GSE_simd::getN3() << endl;
	cout << "Nd:" << GSE_simd::getNd() << endl;

	double tauB = GSE_simd::tauB_computation(n, GSE_simd::getN1(), GSE_simd::getN2(), GSE_simd::getN3(), GSE_simd::getNd());

	cout << endl;
	cout << "Kendall's tauB coefficient: " << tauB << endl;

	double overall_end_clock = omp_get_wtime();

	cout << endl;
	cout << "Time for Step1:" << step1_end_clock - step1_start_clock << endl;
	cout << "Time for Step2:" << step2_end_clock - step2_start_clock << endl;
	cout << "Time for Step3:" << step3_end_clock - step3_start_clock << endl;
	cout << "Time for Step4:" << step4_end_clock - step4_start_clock << endl;
	cout << "Overall time:" << overall_end_clock - overall_start_clock << endl;
	cout << endl;

	system("pause");
}

void GSE_simd::setN1(double n) {
	n1 = n;
}

double GSE_simd::getN1() {
	return n1;
}

void GSE_simd::setN2(double n) {
	n2 = n;
}

double GSE_simd::getN2() {
	return n2;
}

void GSE_simd::setN3(double n) {
	n3 = n;
}

double GSE_simd::getN3() {
	return n3;
}

void GSE_simd::setNd(int n) {
	nd = n;
}

int GSE_simd::getNd() {
	return nd;
}
