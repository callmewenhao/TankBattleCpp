//
// Created by zhaowenhao on 2022/7/14.
//

#pragma once
#include <thread>
#include <graphics.h>
#include <vector>
#include "Tank.h"
#include "Bullet.h"


class Hero : public Tank {
public:

    // func
    Hero(int x, int y, int d);
    std::shared_ptr<Bullet> shoot() override;

    // field
    std::vector<std::shared_ptr<Bullet>> bullets; // put the bullets into heap

};




