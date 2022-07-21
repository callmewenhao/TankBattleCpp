//
// Created by zhaowenhao on 2022/7/14.
//

#pragma once

#include <graphics.h>
#include <thread>
#include <iostream>

class Bullet {

public:

    // field
    int x;
    int y;
    int d;
    int speed = 2;
    bool isLive = true;

    // func
    Bullet(int x, int y, int d);

    void run();
};
