#include "XYZ.h"



XYZ::XYZ(float x, float y, float z)
	: x(x), y(y), z(z) 
{}


XYZ::~XYZ()
{
}

std::ostream & operator<<(std::ostream & os, XYZ &xyz)
{
	os << "( " << xyz.x << ", " << xyz.y << ", " << xyz.z << ")" << std::endl;
	return os;
}
