#include "Starter.h"


Starter::Starter()
{
}

Starter::~Starter()
{
}


void Starter::init() {
	vector<Pair> elements;
	for (int i = 0; i < 10000; i++) {
		int first = rand() % 4 + 1;
		int second = rand() % 4 + 1;
		elements.insert(elements.end(), Pair(first, second));
	}

	int method;
	int num_threads;
	cout << "1: naive, 2: GSE" << endl;
	cin >> method;
	cout << "insert number of threads:" << endl;
	cin >> num_threads;
	cout << endl;

	if (method == 1) {
		Naive naive;
		naive.calculate_tau_a(elements, num_threads);
	}
	if (method == 2) {
		GSE gse;
		gse.calculate_tau_b(elements, num_threads);
	}
}



int main() {
	Starter starter;
	starter.init();
	return 0;
}