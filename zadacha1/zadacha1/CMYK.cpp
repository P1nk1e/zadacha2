#include "CMYK.h"



CMYK::CMYK(float c, float m, float y, float k) 
	: c(c), m(m), y(y), k(k)
{}


CMYK::~CMYK()
{
}

std::ostream & operator<<(std::ostream & os, CMYK & cmyk)
{
	os << "( " << cmyk.c << ", " << cmyk.m << ", " << cmyk.y << ", " << cmyk.k << ")" << std::endl;
	return os;
}
