#include <iostream>
#include <conio.h>
#include <graphics.h>
#include "Game.h"

int main() {

    initgraph(1000, 700);    // 创建绘图窗口，大小为 640x480 像素

    // our main thread
    Game game;
    std::thread paintPanel(&Game::play, &game); // a ref or ptr for second para
    paintPanel.join();

//    closegraph();            // 关闭绘图窗口
    return 0;

}

