//
// Created by zhaowenhao on 2022/7/14.
//

#include "Bullet.h"

Bullet::Bullet(int x, int y, int d) : x(x), y(y), d(d) {}

void Bullet::run() {
    while (true) {
        switch (d) {
            case 0:
                if (y > 0) {
                    y -= speed;
                } else isLive = false;
                break;
            case 1:
                if (x < 1000) {
                    x += speed;
                } else isLive = false;
                break;
            case 2:
                if (y < 700) {
                    y += speed;
                } else isLive = false;
                break;
            case 3:
                if (x > 0) {
                    x -= speed;
                } else isLive = false;
                break;
            default:
                break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//        std::cout << x << " " << y << std::endl;

        if (!(this->isLive)) {
            std::cout << "this thread is dead!" << std::endl;
            break;
        }
    }
}


