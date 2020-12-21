#pragma once
#include "Header.h"
class CMYK
{
public:
	CMYK(float = 0, float = 0, float = 0, float = 0);
	~CMYK();
	float c, m, y, k;
};


std::ostream& operator<<(std::ostream&, CMYK&);

