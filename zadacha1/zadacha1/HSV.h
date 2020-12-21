#pragma once
#include "Header.h"
class HSV
{
public:
	HSV(int h = 0, float s = 0, float v = 0);
	~HSV();
	int h;
	float s, v;
	//bool his;
};

std::ostream& operator<<(std::ostream&, HSV&);
