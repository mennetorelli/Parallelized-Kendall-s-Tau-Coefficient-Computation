#include "Step1.h"
#include <iostream>

Step1::Step1()
{
	setN1(0);
	setN3(0);
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

int main() {
	Step1 step1;

	vector<Pair> elements = { Pair(4,4), Pair(1,3), Pair(2,2), Pair(1,3), Pair(3,1), Pair(1,2), Pair(4,3), Pair(2,2)};

	step1.quicksort(elements, 0, elements.size()-1);

	for (int i = 0; i < elements.size(); i++) {
		cout << "(" << elements[i].getFirst() << "," << elements[i].getSecond() << ")" << endl;
	}

	step1.scan(elements, 0);

	cout << "\nN1:" << step1.getN1() << endl;
	cout << "\nN3:" << step1.getN3() << endl;

	system("pause");
	return 0;
}
