#include "Starter.h"


Starter::Starter()
{
}

Starter::~Starter()
{
}


void Starter::init() {
	vector<Pair> elements;

	string input_choice;
	cout << "Generate new input file? (y/n) ";
	cin >> input_choice;
	if (input_choice == "y") {
		Starter::generate_input_file();
	}
	Starter::read_input_file(elements);


	int method;
	int num_threads;
	cout << endl;
	cout << "Select method: 1) naive, 2) GSE, 3) GSE_simd ";
	cin >> method;
	cout << "insert number of threads: ";
	cin >> num_threads;
	cout << endl;


	if (method == 1) {
		Naive naive;
		naive.naive_algorithm(elements, num_threads);
	}

	if (method == 2) {
		GSE gse;
		gse.GSE_algorithm(elements, num_threads);
	}

	if (method == 3) {
		GSE_simd gse_simd;
		gse_simd.GSE_algorithm(elements, num_threads);
	}
}


void Starter::generate_input_file() {
	srand(time(NULL));
	int vector_size;
	int range;
	cout << "Insert vector size: ";
	cin >> vector_size;
	cout << "Insert range: ";
	cin >> range;

	cout << "Generating a new file..." << endl;
	ofstream file("input.txt");
	for (int i = 0; i < vector_size; i++) {
		int value = rand() % range + 1;
		if (file.is_open())
		{
			file << value << " ";
		}
	}
	file << endl;
	for (int i = 0; i < vector_size; i++) {
		int value = rand() % range + 1;
		if (file.is_open())
		{
			file << value << " ";
		}
	}
	file << endl;
	file.close();
}

void Starter::read_input_file(vector<Pair> &elements) {
	cout << "Reading data from file..." << endl;
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

	for (int i = 0; i < vectors[0].size(); i++) {
		elements.insert(elements.end(), Pair(vectors[0].at(i), vectors[1].at(i)));
	}
}


int main() {
	Starter starter;
	starter.init();

	return 0;
}
