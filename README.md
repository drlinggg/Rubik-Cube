# 🗁 3x3 rotatable model of rubik cube!! 🗁
вау!

![image](https://github.com/drlinggg/Rubik-Cube/assets/124909828/b8364b06-5b7a-4031-a515-46c75a266fe8)

ого! (can be shuffled and solved by 6 step algorithm)

## 🛠️ Build & Run: 🛠️
- Native:
  ```bash
  sudo pacman -S glfw
  sudo pacman -S glut
  sudo pacman -S glew
  g++ -std=c++17 main.cpp cubeDLG.cpp cube.cpp smallCube.cpp Shader.cpp -lglfw -lGL -lglut -lGLEW
  ```
- Dockerfile:
    ```Docker
    docker build . -t rubik
    docker run -v './out:/opt/app/out' rubik
    ```
    

## 📝 [A short example](https://youtu.be/6bWaojql_bY?si=bxfw6jH2gpzUFyPI) 📝
  - wasd-camera
  - 1-8 moves
  - 9 shuffle
  - 0 solve
  - P increase turnSpeed
  - M decrease turnSpeed


I was learning a lot basic stuff like Docker OpenGL and even md syntax and I guess there could be only twenty commits but I prefer quicksaving every 5 minutes
