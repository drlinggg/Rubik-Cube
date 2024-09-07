FROM archlinux

RUN mkdir -p -m 0700 /run/user/0
##       ^-- now you also have this last line
ENV XDG_RUNTIME_DIR=/run/user/0
## ^-- And still that one

WORKDIR /opt/app

RUN pacman -Sy --noconfirm && 
    pacman -S glfw --noconfirm && 
    pacman -S glut --noconfirm && 
    pacman -S glew --noconfirm && 
    pacman -S glm --noconfirm && 
    pacman -S libgl --noconfirm && 
    pacman -S gcc --noconfirm

COPY . .

VOLUME /opt/app

CMD ["g++", "main.cpp", "cubeDLG.cpp", "cube.cpp", "smallCube.cpp", "Shader.cpp", "-o", "./a.out", "-lglfw", "-lGL", "-lglut", "-lGLEW"]
