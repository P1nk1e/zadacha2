//
//  linesMod.cpp
//  anti-aliasing
//
//  Created by Владимир Киселев on 21.12.2020.
//  Copyright © 2020 Владимир Киселев. All rights reserved.
//

#include "linesMod.hpp"
#include <algorithm>
#include <cmath>

int mysign(int a) {
    if (a > 0)
        return 1;
    else
        if (a < 0)
            return -1;
        else
            return 0;
}
TGAColor operator*(TGAColor& color, float size) {
    TGAColor clr((int)(color.r * size), (int)(color.g * size), (int)(color.b * size), (int)(color.a * size));
    return clr;
}
void DrawLine(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor c) {
 bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    float derror = std::abs(dy/float(dx));
    float error = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.set(y, x, c);
        } else {image.set(x, y, c);
        }
        error += derror;

        if (error>.5) {
            y += (y1>y0?1:-1);
            error -= 1.;
        }
    }
}
void lineBrasenhemMod(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color) {
    if ((x1 - x2)*(y1 - y2) == 0) {
        DrawLine(x1, y1, x2, y2, image, color);
    }
    else {
        int I = 255;
        float x = x1;
        float y = y1;
        int px = abs(x2 - x1);
        int py = abs(y2 - y1);
        int signx = mysign(x2 - x1);
        int signy = mysign(y2 - y1);
        float t = I * py / px;
        float e_ = I / 2;
        float emax = I - t;
        if (px > py) {
            image.set(x, y, color * (t / 2));
            for (int i = 0; i < px; ++i) {
                if (e_ >= emax) {
                    y += signy;
                    e_ -= emax;
                }
                else {
                    e_ += t;
                }
                x += signx;
                image.set(x, y, color * (t / 2));
            }
        }
        else {
            image.set(x, y, color * (t / 2));
            for (int i = 0; i < py; ++i) {
                if (e_ >= emax) {
                    x += signx;
                    e_ -= emax;
                }
                else {
                    e_ += t;
                }
                y += signy;
                image.set(x, y, color * (t / 2));
            }
        }
    }


}
void lineVu(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color) {
    if (x1 == x2 || y1 == y2) {
        DrawLine(x1, y1, x2, y2, image, color);
    }
    else {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int signX = mysign(x2 - x1);
        int signY = mysign(y2 - y1);

        if (dx > dy) {
            int x = x1;
            float y = y1;
            while (x != x2) {
                float light_up = abs((int)(y)-y);
                float light_dn = 1 - light_up;

                image.set(int(x), int(y), color * light_up);
                image.set(int(x), int(y - 1), color * light_dn);
                x += signX;
                y += (float)dy / (float)std::max(dx, dy) * signY;
            }
        }
        else {
            float x = x1;
            int y = y1;
            while (y != y2) {
                float light_rt = abs((int)(x)-x);
                float light_lt = 1 - light_rt;

                image.set(int(x), int(y), color * light_rt);
                image.set(int(x - 1), int(y), color * light_lt);

                x += (float)dx / (float)std::max(dx, dy) * signX;
                y += signY;
            }
        }
    }
}
