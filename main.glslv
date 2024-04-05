#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
out vec4 gl_Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	 gl_Position.xyz = vertexPosition_modelspace;
     gl_Position.w = 1*gl_Position.z+1;
     //gl_Position = projection * view * model * gl_Position;
}