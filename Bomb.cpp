//
// Created by zhaowenhao on 2022/7/21.
//

#include "Bomb.h"

void Bomb::lifeDown() {
    if(life > 0) {
        life--;
    } else {
        isLive = false;
    }
}

Bomb::Bomb(int x, int y) : x(x), y(y) {}




