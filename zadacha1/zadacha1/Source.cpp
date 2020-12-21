#include "Header.h"
#include "RGB.h"
#include "CMY.h"
#include "CMYK.h"
#include "HLS.h"
#include "HSV.h"
#include "XYZ.h"


/*
git add .
git commit -am "Название коммита"
git status
git push
*/

int col(int v1) {
	int co = 0;
	while (v1 != 0) {
		v1 = v1 / 10;
		co++;
	}
	return co;
}

void rgb2cmy(RGB & rgb, CMY & cmy) {
	cmy.c = 1 - rgb.r;
	cmy.m = 1 - rgb.g;
	cmy.y = 1 - rgb.b;
}

void cmy2rgb(CMY & cmy, RGB & rgb) {
	rgb.r = 1 - cmy.c;
	rgb.g = 1 - cmy.m;
	rgb.b = 1 - cmy.y;
}

void rgb2cmyk(RGB & rgb, CMYK & cmyk) {
	cmyk.k = std::min(std::min(1 - rgb.r, 1 - rgb.g), 1 - rgb.b);

	if (cmyk.k < 1) {
		cmyk.c = (1 - rgb.r - cmyk.k) / (1 - cmyk.k);
		cmyk.m = (1 - rgb.g - cmyk.k) / (1 - cmyk.k);
		cmyk.y = (1 - rgb.b - cmyk.k) / (1 - cmyk.k);
	}
	else {
		cmyk.c = 1 - rgb.r;
		cmyk.m = 1 - rgb.g;
		cmyk.y = 1 - rgb.b;
	}

}

void cmyk2rgb(CMYK & cmyk, RGB & rgb) {
	rgb.r = 1 - cmyk.c*(1 - cmyk.k) - cmyk.k;
	rgb.g = 1 - cmyk.m*(1 - cmyk.m) - cmyk.k;
	rgb.b = 1 - cmyk.y*(1 - cmyk.y) - cmyk.k;
}
//___HSV___
void rgb2hsv(RGB & rgb, HSV & hsv) {

	int r = (int)(rgb.r * 255);
	int g = (int)(rgb.g * 255);
	int b = (int)(rgb.b * 255);

	int max = (int)std::max(std::max((double)r, (double)g), (double)b);
	int min = (int)std::min(std::min((double)r, (double)g), (double)b);

	//__H____________________________________________________________
	if (max != min) {
		if (max == r && g >= b)
			hsv.h = 60 * (g - b) / (max - min);
		else
			if (max == r && g < b)
				hsv.h = 60 * (g - b) / (max - min) + 360;
			else
				if (max == g)
					hsv.h = 60 * (b - r) / (max - min) + 120;
				else
					if (max == b)
						hsv.h = 60 * (r - g) / (max - min) + 240;
	}
	/*else {
		int * h = &(hsv.h);
		h = NULL;
	}*/

	//__S____________________________________________________________
	if (max == 0)
		hsv.s = 0;
	else {
		float mi = min;
		float ma = max;
		float s = 1 - (mi / ma);
		hsv.s = s;
	}

	//__V____________________________________________________________
	hsv.v = ((float)max) / 255;
}

void hsv2rgb(HSV & hsv, RGB & rgb) {
	
	if (hsv.h != NULL) {

		float vmin = (1 - hsv.s) * hsv.v;
		float a = (hsv.v - vmin) * (hsv.h % 60) / 60;
		float vinc = vmin + a;
		float vdec = hsv.v - a;
		int hi = (hsv.h / 60) % 6;
		switch (hi)
		{
		case 0: {
			rgb.r = hsv.v;
			rgb.g = vinc;
			rgb.b = vmin;
			break;
		}
		case 1: {
			rgb.r = vdec;
			rgb.g = hsv.v;
			rgb.b = vmin;
			break;
		}
		case 2: {
			rgb.r = vmin;
			rgb.g = hsv.v;
			rgb.b = vinc;
			break;
		}
		case 3: {
			rgb.r = vmin;
			rgb.g = vdec;
			rgb.b = hsv.v;
			break;
		}
		case 4: {
			rgb.r = vinc;
			rgb.g = vmin;
			rgb.b = hsv.v;
			break;
		}
		case 5: {
			rgb.r = hsv.v;
			rgb.g = vmin;
			rgb.b = vdec;
			break;
		}
		default:
			break;
		}
	}
	else {
		rgb.r = 0;
		rgb.g = 0;
		rgb.b = 0;
	}
}
//___HLS___
void rgb2hls(RGB & rgb, HLS & hls) {
	float max = std::max(std::max(rgb.r, rgb.g), rgb.b);
	float min = std::min(std::min(rgb.r, rgb.g), rgb.b);
	//___L___
	hls.l = 0.5 * (max + min);
	//___H___
	if (max != min) {
		if(max == rgb.r && rgb.g >= rgb.b)
			hls.h = 60 * (rgb.g - rgb.b) / (max - min);
		else
			if (max == rgb.r && rgb.g < rgb.b) 
				hls.h = 60 * (rgb.g - rgb.b) / (max - min) + 360;
			else 
				if(max == rgb.g)
					hls.h = 60 * (rgb.b - rgb.r) / (max - min) + 120;
				else
					if(max == rgb.b)
						hls.h = 60 * (rgb.r - rgb.g) / (max - min) + 240;
	}
	//___S___
	if (hls.l == 0 || max == min)
		hls.s = 0;
	else
		if (hls.l > 0 && hls.l <= 0.5)
			hls.s = (max - min) / (2 * hls.l);
		else
			if (hls.l < 1 && hls.l > 0.5)
				hls.s = (max - min) / (2 - 2 * hls.l);
			else
				hls.s = (max - min) / ( 1 - abs(1 - max - min) );
}

void hls2rgb(HLS & hls, RGB & rgb) {
	int h = hls.h / 60;
	float c = (1 - abs(2 * hls.l - 1)) * hls.s;
	float x = c * (1 - abs(h % 2 - 1));

	float r, g, b;

	if (hls.h == NULL) {
		r = 0;
		g = 0;
		b = 0;
	}
	else
		if (h >= 0 && h < 1) {
			r = c;	
			g = x;	
			b = 0;
		}
		else
			if (h >= 1 && h < 2) {
				r = x;	
				g = c;	
				b = 0;
			}
			else
				if (h >= 2 && h < 3) {
					r = 0;
					g = c;
					b = x;
				}
				else
					if (h >= 3 && h < 4) {
						r = 0;
						g = x;
						b = c;
					}
					else
						if (h >= 4 && h < 5) {
							r = x;
							g = 0;
							b = c;
						}
						else
							if (h >= 5 && h < 6) {
								r = c;
								g = 0;
								b = x;
							}

	float m = hls.l - 0.5 * c;

	rgb.r = r + m;
	rgb.g = g + m;
	rgb.b = b + m;
}
//___XYZ___
void rgb2xyz(RGB & rgb, XYZ & xyz) {
	xyz.x = (0.4900 * rgb.r		+ 0.3100 * rgb.g	+ 0.2000 * rgb.b)	/ 0.17697;
	xyz.y = (0.1770 * rgb.r		+ 0.8124 * rgb.g	+ 0.0106 * rgb.b)	/ 0.17697;
	xyz.z = (0.0000 * rgb.r		+ 0.0100 * rgb.g	+ 0.9900 * rgb.b)	/ 0.17697;
}

void xyz2rgb(XYZ & xyz, RGB & rgb) {
	rgb.r = ( 0.4185 * xyz.x	+ -0.1587 * xyz.y	+ -0.0828 * xyz.z);
	rgb.g = (-0.0912 * xyz.x	+  0.2524 * xyz.y	+  0.0157 * xyz.z);
	rgb.b = ( 0.0009 * xyz.x	+ -0.0025 * xyz.y	+  0.1786 * xyz.z);
}


int main() {
	setlocale(LC_ALL, "Russian");

	RGB		rgb		(0, 0, 0	);
	CMY		cmy		(0, 0, 0	);
	CMYK	cmyk	(0, 0, 0, 0	);
	HSV		hsv		(0, 0, 0	);
	HLS		hls		(0, 0, 0	);
	XYZ		xyz		(0, 0, 0	);
	
	int c = 1, intv1, intv2;
	float floatv1, floatv2, floatv3, floatv4;

	while (c != 0) {
		std::cout << "0: exit " << std::endl;
		std::cout << "1: rgb            - 3 вещестевнных числа [ 0, 1 ]" << std::endl;
		std::cout << "2: cmy            - 3 вещестевнных числа [ 0, 1 ]" << std::endl;
		std::cout << "3: cmyk           - 4 вещестевнных числа [ 0, 1 ]" << std::endl;
		std::cout << "4: hsv            - целый угол [ 0, 255 ] и 2 вещественных числа [ 0, 1 ]" << std::endl;
		std::cout << "5: hls            - целый угол [ 0, 255 ] и 2 вещественных числа [ 0, 1 ]" << std::endl;
		std::cout << "6: xyz            - 3 вещестевнных числа [ 0, 1 ]" << std::endl;

		std::cin >> c;

		switch (c) {
		case 1: {
			std::cout << "введите через пробел 3 вещественных числа от 0 до 1: ";
			std::cin >> floatv1 >> floatv2 >> floatv3;
			rgb.r = floatv1;
			rgb.g = floatv2;
			rgb.b = floatv3;

			break;
		}
		case 2: {
			std::cout << "введите через пробел 3 вещественных числа от 0 до 1: ";
			std::cin >> floatv1 >> floatv2 >> floatv3;
			cmy.c = floatv1;
			cmy.m = floatv2;
			cmy.y = floatv3;

			cmy2rgb(cmy, rgb);
			break;
		}
		case 3: {
			std::cout << "введите через пробел 4 вещественных числа от 0 до 1: ";
			std::cin >> floatv1 >> floatv2 >> floatv3 >> floatv4;
			cmyk.c = floatv1;
			cmyk.m = floatv2;
			cmyk.y = floatv3;
			cmyk.k = floatv4;

			cmyk2rgb(cmyk, rgb);
			break;
		}
		case 4: {

			std::cout << "введите через пробел 3 числа: 1 целое и два вещественных от 0 до 1: ";
			std::cin >> intv1 >> floatv2 >> floatv3 ;

			hsv.h = intv1;
			hsv.s = floatv2;
			hsv.v = floatv3;

			hsv2rgb(hsv, rgb);
			break;
		}
		case 5: {
			std::cout << "введите через пробел 3 числа: 1 целое и два вещественных от 0 до 1: ";
			std::cin >> intv1 >> floatv2 >> floatv3;
			hls.h = intv1;
			hls.l = floatv2;
			hls.s = floatv3;

			hls2rgb(hls, rgb);
			break;
		}
		default: {
			std::cout <<"error" << std::endl;
			break;
		}
		case 6: {
			std::cout << "введите через пробел 3 вещественных числа от 0 до 1: ";
			std::cin >> floatv1 >> floatv2 >> floatv3;
			xyz.x = floatv1;
			xyz.y = floatv2;
			xyz.z = floatv3;

			xyz2rgb(xyz, rgb);
			break; 
		}
		}

		rgb2cmy(rgb, cmy);
		rgb2cmyk(rgb, cmyk);
		rgb2hsv(rgb, hsv);
		rgb2hls(rgb, hls);
		rgb2xyz(rgb, xyz);

		std::cout << "=========================================" << std::endl;
		std::cout << "RGB  : " << rgb;
		std::cout << "CMY  : " << cmy;
		std::cout << "CMYK : " << cmyk;
		std::cout << "HSV  : " << hsv;
		std::cout << "HSL  : " << hls;
		std::cout << "XYZ  : " << xyz;
		std::cout << "=========================================" << std::endl;


	}
	return 0;
}