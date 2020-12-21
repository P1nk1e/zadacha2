#pragma once
#include "Header.h"
class CMY
{
public:
	float c=0, m=0, y=0;
	CMY(float, float, float);
	~CMY();
};

std::ostream& operator<<(std::ostream&, CMY&);
