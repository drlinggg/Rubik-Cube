#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	 gl_Position.xyz = vertexPosition_modelspace;
     gl_Position.w = 1.0;
     //gl_Position = projection * view * model * gl_Position;
}