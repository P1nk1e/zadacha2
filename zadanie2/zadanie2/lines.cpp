//
//  lines.cpp
//  zadanie2
//
//  Created by Владимир Киселев on 20.12.2020.
//  Copyright © 2020 Владимир Киселев. All rights reserved.
//

#include "lines.hpp"
#include <cmath>

const double PI = 3.1415;

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

void DrawLineDDA(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color) {
        float dx = x2 - x1;
        float dy = y2 - y1;
    
        float max = std::max(abs(dx), abs(dy));
        float e = 1 / max;
    
        float x = x1;
        float y = y1;
        for (int i = 0; i != max; ++i) {
            image.set(x + 0.5, y + 0.5, color);
            x += dx * e;
            y += dy * e;
        }
    }

void circleBrasenhem(int x0, int y0, int r, TGAImage &image, TGAColor color) {
    int x = 0;
    int y = r;
    int delta = 1 - 2 * r;
    int error = 0;
    while (y >= 0) {
        image.set(x0 + x, y0 + y, color);
        image.set(x0 + x, y0 - y, color);
        image.set(x0 - x, y0 + y, color);
        image.set(x0 - x, y0 - y, color);
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)) {
            delta += 2 * (++x) + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)) {
            delta -= 2 * (--y) + 1;
            continue;
        }
        delta += 2 * ((++x) - (--y));
    }
}
void circleDDA(int x0, int y0, int r, TGAImage &image, TGAColor color) {
    float y = r;
    float stop = (float)r / sqrt(2.) + 1;
    for (int x = 0; x < stop; ++x) {
        image.set((int)((float)x0 + x + 0.5), int((float)y0 + y + 0.5), color);
        image.set((int)((float)x0 + x + 0.5), int((float)y0 - y + 0.5), color);
        image.set((int)((float)x0 - x + 0.5), int((float)y0 - y + 0.5), color);
        image.set((int)((float)x0 - x + 0.5), int((float)y0 + y + 0.5), color);
        
        image.set((int)((float)x0 + y + 0.5), int((float)y0 + x + 0.5), color);
        image.set((int)((float)x0 + y + 0.5), int((float)y0 - x + 0.5), color);
        image.set((int)((float)x0 - y + 0.5), int((float)y0 - x + 0.5), color);
        image.set((int)((float)x0 - y + 0.5), int((float)y0 + x + 0.5), color);

        
        y -= (float)x / sqrt(r * r - x * x);
    }

}
void circleParametr(int x0, int y0, int r, TGAImage &image, TGAColor color) {
    int x = r, x1 = r;
    int y = 0, y1 = 0;
    for (int i = 1; i != 45; ++i) {
        x1 = x;
        y1 = y;
        x = r * cos(float(i) / 180.0 * PI);
        y = r * sin(float(i) / 180.0 * PI);

        DrawLine(x0 + x, y0 + y, x0 + x1, y0 + y1, image, color);
        DrawLine(x0 - x, y0 + y, x0 - x1, y0 + y1, image, color);
        DrawLine(x0 - x, y0 - y, x0 - x1, y0 - y1, image, color);
        DrawLine(x0 + x, y0 - y, x0 + x1, y0 - y1, image, color);

        DrawLine(x0 + y, y0 + x, x0 + y1, y0 + x1, image, color);
        DrawLine(x0 - y, y0 + x, x0 - y1, y0 + x1, image, color);
        DrawLine(x0 - y, y0 - x, x0 - y1, y0 - x1, image, color);
        DrawLine(x0 + y, y0 - x, x0 + y1, y0 - x1, image, color);
    }
}
