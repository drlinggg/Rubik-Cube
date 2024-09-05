FROM archlinux

RUN pacman -Sy --noconfirm
RUN pacman -S glfw --noconfirm
RUN pacman -S glut --noconfirm
RUN pacman -S glew --noconfirm
RUN pacman -S glm --noconfirm
RUN pacman -S libgl --noconfirm
RUN pacman -S gcc --noconfirm

COPY . .
WORKDIR .

RUN g++ main.cpp cubeDLG.cpp cube.cpp smallCube.cpp Shader.cpp -o a.out -lglfw -lGL -lglut -lGLEW

CMD ["./a.out"]
