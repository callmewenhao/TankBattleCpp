cmake_minimum_required(VERSION 3.22)
project(Clion_EasyX)

set(CMAKE_CXX_STANDARD 14)

# cmake settings for EasyX
set(EasyX_INC D:\\EasyX\\include) # 你的include地址
set(EasyX_LINK D:\\EasyX\\lib\\VC2015\\x64) # 找与自己的环境配置对应的版本
include_directories(${EasyX_INC})
link_directories(${EasyX_LINK})

#在lib对应的文件夹里面找lib文件（一般只有EasyXa和EasyXw这两个，进行链接）
link_libraries(EasyXa)
link_libraries(EasyXw)

add_executable(Clion_EasyX main.cpp Tank.cpp Tank.h Hero.cpp Hero.h Enemy.cpp Enemy.h Bullet.cpp Bullet.h Game.cpp Game.h Bomb.cpp Bomb.h)
