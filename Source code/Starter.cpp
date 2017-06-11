#include "Starter.h"


Starter::Starter()
{
}

Starter::~Starter()
{
}


void Starter::init() {
	srand(time(NULL));
	vector<Pair> elements;

	/*ofstream myfile("input.txt");
	for (int i = 0; i < 2000000; i++) {
		int value = rand() % 100000 + 1;
		if (myfile.is_open())
		{
			myfile << value << " ";
		}
	}
	myfile << endl;
	for (int i = 0; i < 2000000; i++) {
		int value = rand() % 100000 + 1;
		if (myfile.is_open())
		{
			myfile << value << " ";
		}
	}
	myfile << endl;
	myfile.close();*/

	string line;
	ifstream file("input.txt");
	vector<vector<int>> vectors;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			vector<int> vector;
			istringstream line_stream(line);
			string token;
			while (getline(line_stream, token, ' ')) {
				vector.insert(vector.end(), atoi(token.c_str()));
			}
			vectors.insert(vectors.end(), vector);
		}
	}
	file.close();

	for (int i = 0; i < 2000000; i++) {
		elements.insert(elements.end(), Pair(vectors[0].at(i), vectors[1].at(i)));
	}


	int method;
	int num_threads;
	cout << "1: naive, 2: GSE, 3: GSE_simd" << endl;
	cin >> method;


	if (method == 1) {
		Naive naive;
		naive.calculate_tau_a(elements, num_threads);
	}

	if (method == 2) {
		GSE gse;
		gse.calculate_tau_b(elements, num_threads);
	}

	if (method == 3) {
		GSE_simd gse_simd;
		gse_simd.calculate_tau_b(elements, num_threads);
	}
}


int main() {
	Starter starter;
	starter.init();

	return 0;
}
