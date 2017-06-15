#pragma once

class Pair
{
public:
	Pair(int first, int second);
	~Pair();

	void setFirst(int n);
	int getFirst();
	
	void setSecond(int n);
	int getSecond();

private:
	double first;
	double second;
};

