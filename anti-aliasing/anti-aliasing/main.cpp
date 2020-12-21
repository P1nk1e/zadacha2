//
//  main.cpp
//  anti-aliasing
//
//  Created by Владимир Киселев on 21.12.2020.
//  Copyright © 2020 Владимир Киселев. All rights reserved.
//

#include <iostream>

#include "tgaimage.h"
#include "linesMod.hpp"
#include "linesMod.hpp"


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    
   
    int way = 0;
    std::cout << "1 - Bresenham's modified line algorithm" << std::endl <<
    "2 - syaolin vu" << std::endl << "-> ";
    std::cin >> way;
    
    if (way == 1) { // Bresenham's modified line algorithm
        std::cout << std::endl << "enter x1, y1, x2, x2  ->  ";
        int x1, x2, y1, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;

        lineBrasenhemMod(x1, y1, x2, y2, image, white); // Алгоритм Брезенхема для отрезков
        image.set(x1, y1, red);
        image.set(x2, y2, red);
    }
    
    if (way == 2) { // simple DDA line algorithm
        std::cout << std::endl << "enter x1, y1, x2, x2  ->  ";
        int x1, x2, y1, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        
        lineVu(x1, y1, x2, y2, image, white); // Алгоритм Брезенхема для отрезков
        image.set(x1, y1, red);
        image.set(x2, y2, red);
        
    }
    
    
    
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
