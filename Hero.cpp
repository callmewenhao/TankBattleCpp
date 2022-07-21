//
// Created by zhaowenhao on 2022/7/14.
//

#include "Hero.h"

Hero::Hero(int x, int y, int d) : Tank(x, y, d) {}

std::shared_ptr<Bullet> Hero::shoot() {
    std::shared_ptr<Bullet> bullet = nullptr;
    switch (d) {
        case 0:
            bullet = std::make_shared<Bullet>(x + 20 - 5, y, 0);
            break;
        case 1:
            bullet = std::make_shared<Bullet>(x + 40, y + 20 - 4, 1);
            break;
        case 2:
            bullet = std::make_shared<Bullet>(x + 20 - 5, y + 40, 2);
            break;
        case 3:
            bullet = std::make_shared<Bullet>(x - 5, y + 20 - 5, 3);
            break;
        default:break;
    }
    return bullet;
}

