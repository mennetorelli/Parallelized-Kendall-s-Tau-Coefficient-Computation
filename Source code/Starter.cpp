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
		int value = rand() % 100 + 1;
		string line;
		if (myfile.is_open())
		{
			myfile << value << " ";
		}
	}
	myfile.close();*/

	string line;
	ifstream file("input.txt");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			istringstream line_stream(line);
			string token;
			while (getline(line_stream, token, ' ')) {
				int first = atof(token.c_str());
				int second = atof(token.c_str());
				elements.insert(elements.end(), Pair(first, second));
			}
		}
	}
	file.close();


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
