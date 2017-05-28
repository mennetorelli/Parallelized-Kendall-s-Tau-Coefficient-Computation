#include "Step1.h"

Step1::Step1()
{
	setN1(0);
	setN2(0);
	setN3(0);
	setNd(0);
}

Step1::~Step1()
{
}

void Step1::swap_elements(vector<Pair> &elements, int pLeft, int pRight) {
	
	Pair tmp = elements[pRight];
	elements[pRight] = elements[pLeft];
	elements[pLeft] = tmp;
}

int Step1::compare_elements(Pair pLeft, Pair pRight) {

	int result = 0;

	if (pLeft.getFirst() > pRight.getFirst()) result = 1;
	if (pLeft.getFirst() < pRight.getFirst()) result = -1;

	if (result == 0) {
		if (pLeft.getSecond() > pRight.getSecond()) result = 1;
		if (pLeft.getSecond() < pRight.getSecond()) result = -1;
	}
	
	return result;
}

void Step1::quicksort(vector<Pair> &elements, int left, int right) {

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

void Step1::scan(vector<Pair> &elements, int control) {

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
					setN3(getN3() + Wi*(Wi - 1) / 2);
					Wi = 1;
				}
			}

			else {
				setN1(getN1() + Ni*(Ni - 1) / 2);
				setN3(getN3() + Wi*(Wi - 1) / 2);
				Ni = 1;
				Wi = 1;
			}
		}

		setN1(getN1() + Ni*(Ni - 1) / 2);
		setN3(getN3() + Wi*(Wi - 1) / 2);
	}


	if (control == 2) {
		int Ni = 1;

		for (int i = 1; i < elements.size(); i++) {
			if (elements[i].getSecond() == elements[i - 1].getSecond()) Ni++;

			else {
				setN2(getN2() + Ni*(Ni - 1) / 2);
				Ni = 1;
			}
		}

		setN2(getN2() + Ni*(Ni - 1) / 2);
	}

}

int Step1::merge(vector<Pair> &input, vector<Pair> &buffer, int left, int mid, int right) {
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

int Step1::divide(vector<Pair> &input, vector<Pair> &buffer, int n) {
	int nd = 0;
	for (int s = 1; s < n; s *= 2) {
		#pragma omp parallel for num_threads(4)
		for (int l = 0; l < n; l += 2 * s) {
			printf("Hello from thread = %d\n", omp_get_thread_num());
			int m = min(l + s, n);
			int r = min(l + 2 * s, n);
			nd += Step1::merge(input, buffer, l, m, r);
		}
		swap(input, buffer);
	}
	return nd;
}

double Step1::tauB_computation(int n, double n1, double n2, double n3, int nd) {
	double result;

	double n0 = n*(n - 1) / 2;
	
	double num = n0 - n1 - n2 + n3 - 2*nd;
	double den = sqrt((n0 - n1)*(n0 - n2));

	result = num / den;

	return result;
}

void Step1::setN1(double n) {
	n1 = n;
}

double Step1::getN1() {
	return n1;
}

void Step1::setN2(double n) {
	n2 = n;
}

double Step1::getN2() {
	return n2;
}

void Step1::setN3(double n) {
	n3 = n;
}

double Step1::getN3() {
	return n3;
}

void Step1::setNd(int n) {
	nd = n;
}

int Step1::getNd() {
	return nd;
}

int main() {
	Step1 step1;

	vector<Pair> elements = { Pair(4,4), Pair(1,3), Pair(2,2), Pair(1,3), Pair(3,1), Pair(1,2), Pair(4,3), Pair(2,2), Pair(5,2)};
	vector<Pair> buffer = elements;
	int n = elements.size();

	step1.quicksort(elements, 0, n-1);

	for (int i = 0; i < elements.size(); i++) {
		cout << "(" << elements[i].getFirst() << "," << elements[i].getSecond() << ") ";
	}
	cout << endl;

	step1.scan(elements, 1);

	step1.setNd(step1.divide(elements, buffer, n));

	for (int i = 0; i < elements.size(); i++) {
		cout << "(" << elements[i].getFirst() << "," << elements[i].getSecond() << ") ";
	}
	cout << "\n" << endl;

	step1.scan(elements, 2);

	cout << "N1:" << step1.getN1() << endl;
	cout << "N2:" << step1.getN2() << endl;
	cout << "N3:" << step1.getN3() << endl;
	cout << "Nd:" << step1.getNd() << endl;

	double tauB = step1.tauB_computation(n, step1.getN1(), step1.getN2(), step1.getN3(), step1.getNd());

	cout << endl;
	cout << "Kendall's tauB coefficient: " << tauB << endl;

	system("pause");
	return 0;
}
