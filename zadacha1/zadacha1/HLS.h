#pragma once
#include "Header.h"
class HLS
{
public:
	HLS(int h, float s, float l);
	~HLS();
	float s, l;
	int h;
};

std::ostream& operator<<(std::ostream& os, HLS& hls);

