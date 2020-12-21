#include "HLS.h"


std::ostream & operator<<(std::ostream & os, HLS & hls)
{
	os << "( ";
	if (hls.h == NULL)
		os << "NaN";
	else
		os << hls.h;
	os << ", " << hls.s << ", " << hls.l << ")" << std::endl;
	return os;
}

HLS::HLS(int h, float s, float l)
	:h(h), s(s), l(l) 
{}


HLS::~HLS()
{
}
