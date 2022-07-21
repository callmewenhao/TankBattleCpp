//
// Created by zhaowenhao on 2022/7/14.
//

#include "Enemy.h"

std::uniform_int_distribution<unsigned> randomDirection(0, 3);
std::default_random_engine e;

Enemy::Enemy(int x, int y, int d) : Tank(x, y, d) {}

void Enemy::run() {

    while(true) {
        shoot();

        switch (d) {
            case 0:
                for (int i = 0; i < 30; ++i) {
                    if(y > 0) {
                        move();
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                break;
            case 1:
                for (int i = 0; i < 30; ++i) {
                    if(x + 40 < 1000) {
                        move();
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                break;
            case 2:
                for (int i = 0; i < 30; ++i) {
                    if(y + 40 < 700) {
                        move();
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                break;
            case 3:
                for (int i = 0; i < 30; ++i) {
                    if(x > 0) {
                        move();
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                break;
            default:break;
        }

        this->d = randomDirection(e);

        if(!isLive) {
            break;
        }

    }
}

std::shared_ptr<Bullet> Enemy::shoot() {
    std::shared_ptr<Bullet> bullet = nullptr;
    if(bullets.size() < 2) {
        switch (d) {
            case 0:
                bullet = std::make_shared<Bullet>(x + 20 - 5, y, 0);
                break;
            case 1:
                bullet = std::make_shared<Bullet>(x + 40, y + 20 - 4, 1);
                break;
            case 2:
                bullet = std::make_shared<Bullet>(x + 20 - 5, y + 40, 2);
                break;
            case 3:
                bullet = std::make_shared<Bullet>(x - 5, y + 20 - 5, 3);
                break;
            default:break;
        }

        bullets.push_back(bullet);

        //start the thread
        std::thread t(&Bullet::run, bullet);
        t.detach();
    }

    return bullet;
}

