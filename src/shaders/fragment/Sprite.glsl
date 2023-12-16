#version 330 core

in vec2 texturePosition;
out vec4 fragmentColor;

uniform sampler2D sprite;
uniform vec4 spriteColor;

void main()
{
    fragmentColor = vec4(spriteColor) * texture(sprite, texturePosition);
    if (fragmentColor.w < 1)
        discard;
}