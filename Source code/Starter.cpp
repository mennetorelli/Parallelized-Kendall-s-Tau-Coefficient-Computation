#include "Starter.h"


Starter::Starter()
{
}

Starter::~Starter()
{
}


void Starter::init() {
	GSE step1;

	vector<Pair> elements = { Pair(4,4), Pair(1,3), Pair(2,2), Pair(1,3), Pair(3,1), Pair(1,2), Pair(4,3), Pair(2,2), Pair(5,2) };
	vector<Pair> buffer = elements;
	int n = elements.size();

	step1.quicksort(elements, 0, n - 1);

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
}



int main() {
	Starter starter;
	starter.init();
	return 0;
}