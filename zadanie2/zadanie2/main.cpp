//
//  main.cpp
//  zadanie2
//
//  Created by Владимир Киселев on 05.10.2020.
//  Copyright © 2020 Владимир Киселев. All rights reserved.
//

#include <iostream>

#include "tgaimage.hpp"
#include "lines.hpp"
#include "lines.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    
   
    int way = 0;
    std::cout << "1 - Bresenham's line algorithm" << std::endl <<
    "2 - simple DDA line algorithm" << std::endl <<
    "3 - DDA circle algorithm" << std::endl <<
    "4 - Parametric circle algorithm" << std::endl <<
    "5 - Bresenham's circle algorithm" << std::endl;
    std::cout << "enter the number ->  ";
    std::cin >> way;
    
    if (way == 1) { // Bresenham's line algorithm
        std::cout << std::endl << "enter x1, y1, x2, x2  ->  ";
        int x1, x2, y1, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;

        DrawLine(x1, y1, x2, y2, image, white); // Алгоритм Брезенхема для отрезков
        image.set(x1, y1, red);
        image.set(x2, y2, red);
    }
    
    if (way == 2) { // simple DDA line algorithm
        std::cout << std::endl << "enter x1, y1, x2, x2  ->  ";
        int x1, x2, y1, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        
        DrawLineDDA(x1, y1, x2, y2, image, white); // Алгоритм Брезенхема для отрезков
        image.set(x1, y1, red);
        image.set(x2, y2, red);
        
    }
    
    if (way == 3) { // DDA circle algorithm
        std::cout << std::endl << "enter x0, y0, R  ->  ";
        int x0, y0, R;
        std::cin >> x0 >> y0 >> R;
        circleDDA(x0,y0, R, image, white);
        image.set(x0, y0, red);
        
        
    }
    
    if (way == 4) { // Parametric circle algorithm
        std::cout << std::endl << "enter x0, y0, R  ->  ";
        int x0, y0, R;
        std::cin >> x0 >> y0 >> R;
        circleParametr(x0,y0, R, image, white);
        image.set(x0, y0, red);
    }
    
    if (way == 5) { // Bresenham's circle algorithm
        std::cout << std::endl << "enter x0, y0, R  ->  ";
       int x0, y0, R;
       std::cin >> x0 >> y0 >> R;
       circleBrasenhem(x0,y0, R,image, white);
       image.set(x0, y0, red);
    }
    
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
