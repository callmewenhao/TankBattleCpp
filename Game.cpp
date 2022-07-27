//
// Created by zhaowenhao on 2022/7/20.
//

#include "Game.h"

void Game::drawBombs() {
    for (auto bombIter = bombs.begin(); bombIter != bombs.end(); ) {
        if ((*bombIter)->life > 6) {
            putimage((*bombIter)->x, (*bombIter)->y, &bomb1);
        } else if ((*bombIter)->life > 3) {
            putimage((*bombIter)->x, (*bombIter)->y, &bomb2);
        } else { // note: bomb's 'isLive' is false when life == 0
            putimage((*bombIter)->x, (*bombIter)->y, &bomb3);
        }

        if((*bombIter)->life > 0) {
            ++bombIter;
            continue;
        }

        if (!(*bombIter)->isLive) {
            bombIter = bombs.erase(bombIter);
        }
    }
}

void Game::hitTank(std::shared_ptr<Bullet> bullet, std::shared_ptr<Tank> tank) {

    if(tank->x < bullet->x && bullet->x < tank->x + 40
       && tank->y < bullet->y && bullet->y < tank->y + 40) {
        bullet->isLive = false;
        tank->isLive = false;

        // build a bomb
        auto bomb = std::make_shared<Bomb>(tank->x, tank->y);
        bombs.push_back(bomb);
        // thread for bomb
        std::thread t(&Bomb::run, bomb);
        t.detach();
    }
}

void Game::hitEnemy() {
    for (auto bullet : hero->bullets) {
        if (bullet->isLive) { // bullet judge
            for(auto enemy : enemyArr) {
                hitTank(bullet, enemy);
            }
        }
    }
}

void Game::drawEnemyBullets() {

    for (auto& enemy: enemyArr) {
        for (auto bulletIter = enemy->bullets.begin(); bulletIter != enemy->bullets.end(); ) {
            if((*bulletIter)->isLive) {
                int x = (*bulletIter)->x;
                int y = (*bulletIter)->y;
                switch ((*bulletIter)->d) {
                    case 0:
                        putimage(x, y, &bulletUp);
                        break;
                    case 1:
                        putimage(x, y, &bulletRight);
                        break;
                    case 2:
                        putimage(x, y, &bulletDown);
                        break;
                    case 3:
                        putimage(x, y, &bulletLeft);
                        break;
                    default:
                        break;
                }
                bulletIter++;
            } else {
                bulletIter = enemy->bullets.erase(bulletIter);
            }
        }
    }

}

void Game::drawEnemies() {
    for (auto enemyIter = enemyArr.begin();  enemyIter != enemyArr.end(); ) {
        if((*enemyIter)->isLive) {
            int x = (*enemyIter)->x;
            int y = (*enemyIter)->y;
            switch ((*enemyIter)->d) {
                case 0: // up
                    putimage(x, y, &enemyUp);
                    break;
                case 1: // right
                    putimage(x, y, &enemyRight);
                    break;
                case 2: // down
                    putimage(x, y, &enemyDown);
                    break;
                case 3:
                    putimage(x, y, &enemyLeft);
                    break;
                default:
                    break;
            }
            enemyIter++;
        } else {
            enemyIter = enemyArr.erase(enemyIter);
        }
    }
}

void Game::drawHeroBullets() {
//    std::cout << hero.bullets.size() << std::endl;
    for (auto bulletIter = hero->bullets.begin(); bulletIter != hero->bullets.end();) {
        if ((*bulletIter)->isLive) {
            int x = (*bulletIter)->x;
            int y = (*bulletIter)->y;
            switch ((*bulletIter)->d) {
                case 0:
                    putimage(x, y, &bulletUp);
                    break;
                case 1:
                    putimage(x, y, &bulletRight);
                    break;
                case 2:
                    putimage(x, y, &bulletDown);
                    break;
                case 3:
                    putimage(x, y, &bulletLeft);
                    break;
                default:
                    break;
            }
            bulletIter++; // iter come back
        } else {
            // erase the dead bullet!
            bulletIter = hero->bullets.erase(bulletIter);
        }
    }
}

void Game::drawHero() {
    switch (hero->d) {
        case 0: // up
            putimage(hero->x, hero->y, &tankUp);
            break;
        case 1: // right
            putimage(hero->x, hero->y, &tankRight);
            break;
        case 2: // down
            putimage(hero->x, hero->y, &tankDown);
            break;
        case 3:
            putimage(hero->x, hero->y, &tankLeft);
            break;
        default:
            break;
    }
}

void Game::update() {

    ExMessage exMessage;
    while (isLive) {
        if (peekmessage(&exMessage, EM_KEY, true)) {
            // get message from message queue
            if (exMessage.message == WM_KEYDOWN) {
                std::shared_ptr<Bullet> bullet = nullptr;
                switch (exMessage.vkcode) {
                    case VK_UP:
                        std::cout << "up!" << std::endl;
                        hero->d = 0;
                        hero->move();
                        break;
                    case VK_RIGHT:
                        std::cout << "right!" << std::endl;
                        hero->d = 1;
                        hero->move();
                        break;
                    case VK_DOWN:
                        std::cout << "down!" << std::endl;
                        hero->d = 2;
                        hero->move();
                        break;
                    case VK_LEFT:
                        std::cout << "left!" << std::endl;
                        hero->d = 3;
                        hero->move();
                        break;
                    case VK_TAB: // Tab key for fire
                        if(hero->bullets.size() < 5) {
                            std::cout << "shoot!" << std::endl;
                            // new a bullet
                            bullet = hero->shoot();
                            hero->bullets.push_back(bullet);
                            // bullet thread
                            std::thread t1(&Bullet::run, bullet);
                            t1.detach();
                        }
                        break;
                }
            }
        }

        // hero's bullets hit enemies
        hitEnemy();

        // detect enemy tank crash
        crashEnemy();

        // sleep 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }
}

void Game::paint() {

    while (isLive) {
        if(this->enemyArr.empty()) {
            HWND hWnd = GetHWnd();//获取窗口句柄
            int choose = MessageBox(hWnd, "continue? please choose", "hello bro!" ,MB_OKCANCEL);//设置模态对话框
            if(choose == IDOK) {
                initTanks();
            } else {
                isLive = false; // thread is over!
            }
        }

        // batch paint the images
        BeginBatchDraw();
        // clear panel
        cleardevice();
        // paint enemies bullets
        drawEnemyBullets();
        // paint hero bullets
        drawHeroBullets();
        // paint enemies
        drawEnemies();
        // paint hero
        drawHero();
        // paint bombs
        drawBombs();
        // display the images
        EndBatchDraw();

        // sleep 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

}

Game::Game() {
    // init Enemies
    initTanks();
    // load the images
    loadImages();
}

void Game::crashEnemy() {

    for (auto enemy : enemyArr) {
        if(enemy->isLive && hero->isOverlap(enemy)) {
            enemy->isLive = false;
            // build a bomb
            auto bomb = std::make_shared<Bomb>(enemy->x, enemy->y);
            bombs.push_back(bomb);
            // thread for bomb
            std::thread t(&Bomb::run, bomb);
            t.detach();
        }
    }
}

void Game::initTanks() {
    // init hero
    hero = std::make_shared<Hero>(450, 450, 0);

    // init enemies
    for (int i = 0; i < enemyNum; ++i) {
        auto e = std::make_shared<Enemy>(100 * (i + 1), 200, i % 4, this->enemyArr);
        e->speed = 1;
        enemyArr.push_back(e);
        std::thread t(&Enemy::run, e);
        t.detach();
    }
}

void Game::loadImages() {
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
    loadimage(&bomb1, _T("resources/boom/blast8.gif"));
    loadimage(&bomb2, _T("resources/boom/blast6.gif"));
    loadimage(&bomb3, _T("resources/boom/blast4.gif"));
}





