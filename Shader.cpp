//
// Created by Andrei Banakh on 04.04.2024.
//

#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(int id) : id(id){
}

Shader::~Shader(){
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}

Shader* load_shader(std::string vertexFile, std::string fragmentFile) {
    // Reading Files
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try {
        vShaderFile.open(vertexFile);
        fShaderFile.open(fragmentFile);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return nullptr;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "SHADER::FRAGMENT: compilation failed" << std::endl;
        std::cerr << infoLog << std::endl;
        return nullptr;
    }

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "SHADER::VERTEX: compilation failed" << std::endl;
        std::cerr << infoLog << std::endl;
        return nullptr;
    }

    // Shader Program
    GLuint id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "SHADER::PROGRAM: linking failed" << std::endl;
        std::cerr << infoLog << std::endl;

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return nullptr;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return new Shader(id);
}