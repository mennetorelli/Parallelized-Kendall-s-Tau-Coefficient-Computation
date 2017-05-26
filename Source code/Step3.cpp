#include "Step2.h"
#include <omp.h>
#include <iostream>

using namespace std;


int main()
{
	#pragma omp parallel num_threads(3)
	{
		cout << "Hello World" << endl;
	}
	return 0;
}