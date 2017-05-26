#include "Pair.h"

Pair::Pair(double first, double second)
{
	setFirst(first);
	setSecond(second);
}

Pair::~Pair()
{

}

Pair::setFirst(double n) {
	first = n;
}

Pair::setSecond(double n) {
	second = n;
}

Pair::getFirst() {
	return first;
}

Pair::getSecond() {
	return second;
}
