#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 texturePosition;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * modelMatrix * vec4(vertex.xy, 0.0, 1.0);
    texturePosition = vertex.zw;
}