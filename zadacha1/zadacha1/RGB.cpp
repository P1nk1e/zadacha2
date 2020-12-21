#include "RGB.h"



std::ostream & operator<<(std::ostream & os, RGB & rgb)
{
	os << "( " << rgb.r << ", " << rgb.g << ", " << rgb.b << ")" << std::endl;
	return os;
}

RGB::RGB(float r, float g, float b)
	:r(r), g(g), b(b)
{}

RGB::~RGB()
{
}
