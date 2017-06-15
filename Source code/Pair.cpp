#include "Pair.h"

Pair::Pair(int first, int second)
{
	setFirst(first);
	setSecond(second);
}

Pair::~Pair()
{
}

void Pair::setFirst(int n) {
	Pair::first = n;
}

int Pair::getFirst() {
	return Pair::first;
}

void Pair::setSecond(int n) {
	Pair::second = n;
}

int Pair::getSecond() {
	return Pair::second;
}
