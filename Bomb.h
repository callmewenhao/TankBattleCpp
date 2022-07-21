//
// Created by zhaowenhao on 2022/7/21.
//

#pragma once
#include <thread>
#include <chrono>


class Bomb {
public:
    int x;
    int y;
    int life = 9;
    bool isLive = true;

    Bomb(int x, int y);

    void lifeDown();
    void run() {
        while(isLive) {
            //
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            //
            lifeDown();
        }
    }

};



