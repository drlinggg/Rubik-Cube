![image](https://github.com/drlinggg/Rubik-Cube/assets/124909828/b8364b06-5b7a-4031-a515-46c75a266fe8)

3x3 rotatable model of rubik's cube that can be shuffled and solved by 6 step algorithm

# Installation/Build instructions:

## Windows

  - Download zip https://disk.yandex.ru/d/yRQBSVIuqJSFfQ
  - unzip in lib dir
  - mkdir build
  - cmake .
  - cmale --build there

## Linux
  - delete anything except source files & please fix paths in cubeDLG.cpp 35-41 lines to correct ones
  - g++ -std=c++17 main.cpp -lglfw -lGL -lglut -lGLEW

# A short example:

  https://youtu.be/6bWaojql_bY?si=bxfw6jH2gpzUFyPI
  - wasd-camera
  - 1-8 moves
  - 9 shuffle
  - 0 solve
  - P increase turnSpeed
  - M decrease turnSpeed
