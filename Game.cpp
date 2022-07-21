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

void Game::play() {

    ExMessage exMessage;

    while (true) {
        if (peekmessage(&exMessage, EM_KEY, true)) {
            // new position
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

        //
        hitEnemy();

        // clear panel
        cleardevice();
        // paint hero
        drawHero();
        // paint hero bullets
        drawHeroBullets();
        // paint enemies
        drawEnemies();
        // paint enemies bullets
        drawEnemyBullets();
        //
        drawBombs();

        // sleep 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

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






