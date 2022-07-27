#include <iostream>
#include <conio.h>
#include <graphics.h>
#include "Game.h"

int main() {

    initgraph(1000, 700);    // init the windows

    // our main thread
    Game game;
    std::thread repaint(&Game::paint, &game); // a ref or ptr for second para
    std::thread updateInfo(&Game::update, &game); // a ref or ptr for second para
    repaint.join();
    updateInfo.join();

    closegraph();            // 关闭绘图窗口
    return 0;

}

