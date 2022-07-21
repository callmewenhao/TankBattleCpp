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
    IMAGE tankUp, tankRight, tankDown, tankLeft;
    IMAGE enemyUp, enemyRight, enemyDown, enemyLeft;
    IMAGE bulletUp, bulletRight, bulletDown, bulletLeft;
    IMAGE bomb1, bomb2, bomb3;


    std::shared_ptr<Hero> hero;

    int enemyNum = 6;
    std::vector<std::shared_ptr<Enemy>> enemyArr;

    std::vector<std::shared_ptr<Bomb>> bombs;

    // func
    Game() {
        // init hero
        hero = std::make_shared<Hero>(450, 450, 0);
        // init enemies
        for (int i = 0; i < enemyNum; ++i) {
            auto e = std::make_shared<Enemy>(100 * (i + 1), 200, i % 4);
            e->speed = 1;
            enemyArr.push_back(e);
            std::thread t(&Enemy::run, e);
            t.detach();
        }

        // load the hero images
        loadimage(&tankUp, _T("resources/hero/hero1U.gif"));
        loadimage(&tankRight, _T("resources/hero/hero1R.gif"));
        loadimage(&tankDown, _T("resources/hero/hero1D.gif"));
        loadimage(&tankLeft, _T("resources/hero/hero1L.gif"));

        // load the enemy images
        loadimage(&enemyUp, _T("resources/enemy/enemy1U.gif"));
        loadimage(&enemyRight, _T("resources/enemy/enemy1R.gif"));
        loadimage(&enemyDown, _T("resources/enemy/enemy1D.gif"));
        loadimage(&enemyLeft, _T("resources/enemy/enemy1L.gif"));

        // load the bullet images
        loadimage(&bulletUp, _T("resources/bullet/bullet_up.png"));
        Resize(&bulletUp, 7, 7);
        loadimage(&bulletRight, _T("resources/bullet/bullet_right.png"));
        Resize(&bulletRight, 7, 7);
        loadimage(&bulletDown, _T("resources/bullet/bullet_down.png"));
        Resize(&bulletDown, 7, 7);
        loadimage(&bulletLeft, _T("resources/bullet/bullet_left.png"));
        Resize(&bulletLeft, 7, 7);

        // load bombs images
        loadimage(&bomb1, _T("resources/boom/bomb_1.gif"));
        Resize(&bomb1, 50, 50);
        loadimage(&bomb2, _T("resources/boom/bomb_2.gif"));
        Resize(&bomb2, 50, 50);
        loadimage(&bomb3, _T("resources/boom/bomb_3.gif"));
        Resize(&bomb3, 50, 50);

    }

    void drawBombs();

    void hitEnemy();

    void hitTank(std::shared_ptr<Bullet> bullet, std::shared_ptr<Tank> tank);

    void drawEnemyBullets();

    void drawEnemies();

    void drawHero();

    void drawHeroBullets();

    void play(); // todo: bomb


};