//
// Created by zhaowenhao on 2022/7/14.
//

#pragma once
#include <thread>
#include <chrono>
#include <random>
#include "Tank.h"

class Enemy : public Tank {

public:
    // field
    std::vector<std::shared_ptr<Bullet>> bullets; // put the bullets into heap


    Enemy(int x, int y, int d);
    void run();
    std::shared_ptr<Bullet> shoot() override;

};
