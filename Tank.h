//
// Created by zhaowenhao on 2022/7/12.
//

#pragma once

#include <graphics.h>
#include <memory>
#include "Bullet.h"

class Tank {

public:
    // field
    int x = 0;
    int y = 0;
    int d = 0;
    int speed = 4;
    bool isLive = true;

    // func
    Tank(int x, int y, int d);
    void move();
    virtual std::shared_ptr<Bullet> shoot() = 0; // virtual func

};


