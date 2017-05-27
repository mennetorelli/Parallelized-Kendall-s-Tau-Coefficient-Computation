#pragma once

class Pair
{
public:
	Pair(double first, double second);
	~Pair();

	void setFirst(double n);
	double getFirst();
	
	void setSecond(double n);
	double getSecond();

private:
	double first;
	double second;
};

