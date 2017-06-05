#include "Starter.h"


Starter::Starter()
{
}

Starter::~Starter()
{
}


void Starter::init() {
	srand(time(NULL));
	vector<Pair> dataset;
	/*for (int i = 0; i < 1000; i++) {
		int first = rand() % 100 + 1;
		int second = rand() % 100 + 1;
		elements.insert(elements.end(), Pair(first, second));
	}*/
	//elements = { Pair(1,2), Pair(2,1), Pair(2,2), Pair(1,1) };

	vector<vector<int>> elements = Starter::parse_dataset("GSE3526.GPL570");
	int method;
	int num_threads;
	cout << "1: naive, 2: GSE" << endl;
	cin >> method;
	cout << "insert number of threads:" << endl;
	cin >> num_threads;
	cout << endl;

	if (method == 1) {
		Naive naive;
	//	naive.calculate_tau_a(elements, num_threads);
	}

	if (method == 2) {
		GSE gse;
	//	gse.calculate_tau_b(elements, num_threads);
	}

}

vector<vector<int>> Starter::parse_dataset(string filename) {
	vector<vector<int>> datasets;
	string line;
	ifstream file(filename + ".txt");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			vector<int> sample;
			istringstream line_stream(line);
			string token;
			while (getline(line_stream, token, ' ')) {
				double value = atof(token.c_str());
				sample.insert(sample.end(), value);
			}
			datasets.insert(datasets.end(), sample);
			cout << datasets.size() << " ";
		}
	}
	file.close();
	
	return datasets;
}


int main() {
	Starter starter;
	starter.init();

	return 0;
}