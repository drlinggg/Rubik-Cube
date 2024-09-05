FROM archlinux

RUN mkdir -p -m 0700 /run/user/0
##       ^-- now you also have this last line

ENV XDG_RUNTIME_DIR=/run/user/0
## ^-- And still that one

WORKDIR /opt/app

RUN pacman -Sy --noconfirm
RUN pacman -S glfw --noconfirm
RUN pacman -S glut --noconfirm
RUN pacman -S glew --noconfirm
RUN pacman -S glm --noconfirm
RUN pacman -S libgl --noconfirm
RUN pacman -S gcc --noconfirm


COPY . .

VOLUME /opt/app

CMD ["g++", "main.cpp", "cubeDLG.cpp", "cube.cpp", "smallCube.cpp", "Shader.cpp", "-o", "./a.out", "-lglfw", "-lGL", "-lglut", "-lGLEW"]
