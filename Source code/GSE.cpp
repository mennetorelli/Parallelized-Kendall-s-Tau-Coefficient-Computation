#include "GSE.h"

GSE::GSE()
{
	setN1(0);
	setN2(0);
	setN3(0);
	setNd(0);
}

GSE::~GSE()
{
}

void GSE::swap_elements(vector<Pair> &elements, int pLeft, int pRight) {
	
	Pair tmp = elements[pRight];
	elements[pRight] = elements[pLeft];
	elements[pLeft] = tmp;
}

int GSE::compare_elements(Pair pLeft, Pair pRight) {

	int result = 0;

	if (pLeft.getFirst() > pRight.getFirst()) result = 1;
	if (pLeft.getFirst() < pRight.getFirst()) result = -1;

	if (result == 0) {
		if (pLeft.getSecond() > pRight.getSecond()) result = 1;
		if (pLeft.getSecond() < pRight.getSecond()) result = -1;
	}
	
	return result;
}

void GSE::quicksort(vector<Pair> &elements, int left, int right) {

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

void GSE::scan(vector<Pair> &elements, int control) {

	if (control != 1 && control != 2) {
		cout << "Scan function can take only 1 or 2 as control input" << endl;
		return;
	}

	if(control == 1) {
		int Ni = 1;
		int Wi = 1;

		for (int i = 1; i < elements.size(); i++) {
			if (elements[i].getFirst() == elements[i - 1].getFirst()) {
				Ni++;

				if (elements[i].getSecond() == elements[i - 1].getSecond() &&
					elements[i - 1].getFirst() == elements[i - 1].getSecond()) Wi++;
				else {
					setN3(getN3() + (double) Wi*(Wi - 1) / 2);
					Wi = 1;
				}
			}

			else {
				setN1(getN1() + (double) Ni*(Ni - 1) / 2);
				setN3(getN3() + (double) Wi*(Wi - 1) / 2);
				Ni = 1;
				Wi = 1;
			}
		}

		setN1(getN1() + (double) Ni*(Ni - 1) / 2);
		setN3(getN3() + (double) Wi*(Wi - 1) / 2);
	}


	if (control == 2) {
		int Ni = 1;

		for (int i = 1; i < elements.size(); i++) {
			if (elements[i].getSecond() == elements[i - 1].getSecond()) Ni++;

			else {
				setN2(getN2() + (double) Ni*(Ni - 1) / 2);
				Ni = 1;
			}
		}

		setN2(getN2() + (double) Ni*(Ni - 1) / 2);
	}

}

int GSE::merge(vector<Pair> &input, vector<Pair> &buffer, int left, int mid, int right) {
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

int GSE::divide(vector<Pair> &input, vector<Pair> &buffer, int n) {
	int nd = 0;
	for (int s = 1; s < n; s *= 2) {
		#pragma omp parallel for num_threads(4)
		for (int l = 0; l < n; l += 2 * s) {
			printf("Hello from thread = %d\n", omp_get_thread_num());
			int m = min(l + s, n);
			int r = min(l + 2 * s, n);
			nd += GSE::merge(input, buffer, l, m, r);
		}
		swap(input, buffer);
	}
	return nd;
}

double GSE::tauB_computation(int n, double n1, double n2, double n3, int nd) {
	double result;

	double n0 = (double) n*(n - 1) / 2;
	
	double num = n0 - n1 - n2 + n3 - 2*nd;
	double den = sqrt((n0 - n1)*(n0 - n2));

	result = (double) num / den;

	return result;
}


void GSE::calculate_tau_b(vector<Pair> &input) {

	int n = input.size();

	GSE::quicksort(input, 0, n - 1);

	for (int i = 0; i < input.size(); i++) {
		cout << "(" << input[i].getFirst() << "," << input[i].getSecond() << ") ";
	}
	cout << endl;

	GSE::scan(input, 1);

	vector<Pair> buffer = input;
	GSE::setNd(GSE::divide(input, buffer, n));

	for (int i = 0; i < input.size(); i++) {
		cout << "(" << input[i].getFirst() << "," << input[i].getSecond() << ") ";
	}
	cout << "\n" << endl;

	GSE::scan(input, 2);

	cout << "N1:" << GSE::getN1() << endl;
	cout << "N2:" << GSE::getN2() << endl;
	cout << "N3:" << GSE::getN3() << endl;
	cout << "Nd:" << GSE::getNd() << endl;

	double tauB = GSE::tauB_computation(n, GSE::getN1(), GSE::getN2(), GSE::getN3(), GSE::getNd());

	cout << endl;
	cout << "Kendall's tauB coefficient: " << tauB << endl;

	system("pause");
}

void GSE::setN1(double n) {
	n1 = n;
}

double GSE::getN1() {
	return n1;
}

void GSE::setN2(double n) {
	n2 = n;
}

double GSE::getN2() {
	return n2;
}

void GSE::setN3(double n) {
	n3 = n;
}

double GSE::getN3() {
	return n3;
}

void GSE::setNd(int n) {
	nd = n;
}

int GSE::getNd() {
	return nd;
}

