#include "Pair.h"

Pair::Pair(double first, double second)
{
	setFirst(first);
	setSecond(second);
}

Pair::~Pair()
{

}

void Pair::setFirst(double n) {
	first = n;
}

void Pair::setSecond(double n) {
	second = n;
}

double Pair::getFirst() {
	return first;
}

double Pair::getSecond() {
	return second;
}
