#pragma once
#include "Header.h"
class RGB
{
public:
	
	float r, g, b;
	RGB(float r, float g, float b);
	~RGB();
};

std::ostream& operator<<(std::ostream& os, RGB& rgb);
