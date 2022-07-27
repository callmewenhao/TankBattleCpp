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

Tank::Tank(int x, int y, int d) : x(x), y(y), d(d) {}

bool Tank::isOverlap(std::shared_ptr<Tank> t) const {
    if (t->x <= this->x && this->x <= t->x + 40) {
        if (t->y <= this->y && this->y <= t->y + 40) return true; // left top point
        if (t->y <= this->y + 40 && this->y + 40 <= t->y + 40) return true; // left bottom point
    }
    if (t->x <= this->x + 40 && this->x + 40 <= t->x + 40) {
        if (t->y <= this->y && this->y <= t->y + 40) return true; // right top point
        if (t->y <= this->y + 40 && this->y + 40 <= t->y + 40) return true; // right bottom point
    }
    return false;
}




