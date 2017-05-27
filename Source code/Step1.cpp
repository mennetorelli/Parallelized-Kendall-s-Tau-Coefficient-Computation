#include "Step1.h"
#include <iostream>

Step1::Step1()
{

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

/*int main() {
	Step1 step1;

	vector<Pair> elements = { Pair(1,1), Pair(3,2), Pair(1,2), Pair(2,4), Pair(2,1), Pair(3,1), Pair(1,5), Pair(2,3)};

	step1.quicksort(elements, 0, elements.size()-1);

	for (int i = 0; i < elements.size(); i++) {
		cout << "(" << elements[i].getFirst() << "," << elements[i].getSecond() << ")" << endl;
	}

	system("pause");
	return 0;
}*/
