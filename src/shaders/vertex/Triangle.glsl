#version 330 core

layout (location = 0) in vec2 vertex;

uniform mat4 projectionMatrix;

void main()
{
	gl_Position = projectionMatrix * vec4(vertex, 0.0, 1.0);
}