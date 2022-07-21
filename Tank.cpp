//
// Created by zhaowenhao on 2022/7/12.
//

#include "Tank.h"

void Tank::move() {
    switch (d) {
        case 0:
            y -= speed;
            break;
        case 1:
            x += speed;
            break;
        case 2:
            y += speed;
            break;
        case 3:
            x -= speed;
            break;
        default:
            break;
    }
}


Tank::Tank(int x, int y, int d) : x(x), y(y), d(d){}




