#include "Starter.h"


Starter::Starter()
{
}

Starter::~Starter()
{
}


void Starter::init() {
	//vector<Pair> elements = { Pair(4,4), Pair(1,3), Pair(2,2), Pair(1,3), Pair(3,1), Pair(1,2), Pair(4,3), Pair(2,2), Pair(5,2) };
	vector<Pair> elements = { Pair(1,2), Pair(2,4), Pair(5,1), Pair(3,6), Pair(4,3), Pair(6,5) };

	int method;
	int num_threads;
	cout << "1: naive, 2: GSE" << endl;
	cin >> method;
	cout << "insert number of threads:" << endl;
	cin >> num_threads;

	if (method == 1) {
		Naive naive;
		naive.calculate_tau_a(elements);
	}
	if (method == 2) {
		GSE gse;
		gse.calculate_tau_b(elements);
	}
}



int main() {
	Starter starter;
	starter.init();
	return 0;
}