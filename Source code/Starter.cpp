#include "Starter.h"


Starter::Starter()
{
}

Starter::~Starter()
{
}


void Starter::init() {
	vector<vector<int>> input;
	vector<int> u, v;

	string input_choice;
	cout << "Generate new input file? (y/n) ";
	cin >> input_choice;
	if (input_choice == "y") {
		Starter::generate_input_file();
	}
	int n = Starter::read_input_file(input, u, v);

	int method;
	int num_threads;
	cout << endl;
	cout << "Select method: 1) Naive, 2) GSE, 3) Naive_simd ";
	cin >> method;
	cout << "insert number of threads: ";
	cin >> num_threads;
	cout << endl;


	if (method == 1) {
		Naive naive;
		naive.naive_algorithm(u, v, n, num_threads);
	}

	if (method == 2) {
		GSE gse;
		gse.GSE_algorithm(u, v, n, num_threads);
	}

	if (method == 3) {
		Naive_simd naive_simd;
		naive_simd.naive_algorithm(u, v, n, num_threads);
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
	for (int i = 0; i < 2; i++) {
		for (int i = 0; i < vector_size; i++) {
			int value = rand() % range + 1;
			if (file.is_open())
			{
				file << value << " ";
			}
		}
		file << endl;
	}
	file.close();
}

int Starter::read_input_file(vector<vector<int>> &input, vector<int> &u, vector<int> &v) {
	cout << "Reading data from file..." << endl;
	string line;
	ifstream file("input.txt");
	
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
			input.insert(input.end(), vector);
		}
	}
	file.close();

	int n = input[0].size();
	for (int i = 0; i < n; i++) {
		u.insert(u.end(), input[0][i]);
		v.insert(v.end(), input[1][i]);
	}
	return n;
}


int main() {
	Starter starter;
	starter.init();

	return 0;
}
