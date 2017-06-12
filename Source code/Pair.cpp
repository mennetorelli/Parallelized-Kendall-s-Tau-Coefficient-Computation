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
	Pair::first = n;
}

double Pair::getFirst() {
	return Pair::first;
}

void Pair::setSecond(double n) {
	Pair::second = n;
}

double Pair::getSecond() {
	return Pair::second;
}
