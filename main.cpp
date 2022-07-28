#include <iostream>
#include <conio.h>
#include <graphics.h>
#include "Game.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

int main() {

    // play the music
    PlaySound(TEXT("resources/audios/start.wav"), nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP );
    //
    initgraph(1000, 700);  // init the windows
    // our main thread
    Game game;
    std::thread repaint(&Game::paint, &game); // a ref or ptr for second para
    std::thread updateInfo(&Game::update, &game); // a ref or ptr for second para
    repaint.join();
    updateInfo.join();
    //
    closegraph();
    return 0;

}

