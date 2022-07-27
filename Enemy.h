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
    std::vector<std::shared_ptr<Enemy>>& enemyArr; // ref to the enemyArr in Game class

    Enemy(int x, int y, int d, std::vector<std::shared_ptr<Enemy>>& enemies);
    void run();
    std::shared_ptr<Bullet> shoot() override;
    bool enemyOverlaps();


};
