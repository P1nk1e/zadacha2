//
//  lines.hpp
//  zadanie2
//
//  Created by Владимир Киселев on 20.12.2020.
//  Copyright © 2020 Владимир Киселев. All rights reserved.
//

#ifndef lines_hpp
#define lines_hpp

#include <stdio.h>
#include "tgaimage.hpp"

void DrawLine(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color);
void DrawLineDDA(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color);

void circleBrasenhem(int x0, int y0, int radius, TGAImage &image, TGAColor color);
void circleDDA(int x0, int y0, int radius, TGAImage &image, TGAColor color);
void circleParametr(int x0, int y0, int radius, TGAImage &image, TGAColor color);


#endif /* lines_hpp */
