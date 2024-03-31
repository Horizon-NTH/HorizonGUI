#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec4 vertexColor;

out vec4 color;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * modelMatrix * vec4(vertex, 0.0, 1.0);
    color = vertexColor;
}