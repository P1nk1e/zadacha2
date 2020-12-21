//
//  linesMod.hpp
//  anti-aliasing
//
//  Created by Владимир Киселев on 21.12.2020.
//  Copyright © 2020 Владимир Киселев. All rights reserved.
//

#ifndef linesMod_hpp
#include "tgaimage.h"

#include <stdio.h>

int mysign(int a);
TGAColor operator*(TGAColor& color, float size);
void drawLine(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color);
void lineBrasenhemMod(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color);
float fpart(float x);
void lineVu(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color);
#endif /* linesMod_hpp */
