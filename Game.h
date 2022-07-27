//
// Created by zhaowenhao on 2022/7/20.
//

#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include "Tank.h"
#include "Bullet.h"
#include "Hero.h"
#include "Enemy.h"
#include "Bomb.h"

class Game {
public:

    // field
    bool isLive = true;

    IMAGE tankUp, tankRight, tankDown, tankLeft;
    IMAGE enemyUp, enemyRight, enemyDown, enemyLeft;
    IMAGE bulletUp, bulletRight, bulletDown, bulletLeft;
    IMAGE bomb1, bomb2, bomb3;

    std::shared_ptr<Hero> hero;

    int enemyNum = 6;
    std::vector<std::shared_ptr<Enemy>> enemyArr;

    std::vector<std::shared_ptr<Bomb>> bombs;

    // init func
    Game();

    void initTanks();

    void loadImages();

    void drawBombs();

    void hitEnemy();

    void hitTank(std::shared_ptr<Bullet> bullet, std::shared_ptr<Tank> tank);

    void drawEnemyBullets();

    void drawEnemies();

    void drawHero();

    void drawHeroBullets();

    void update();

    void paint();

    void crashEnemy();

};