#pragma once
#include "Header.h"
class XYZ
{
public:
	XYZ(float = 0, float = 0, float = 0);
	~XYZ();
	float x, y, z;
};

std::ostream& operator<<(std::ostream&, XYZ &);
