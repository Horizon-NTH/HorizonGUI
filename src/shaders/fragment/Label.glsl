#version 330 core

in vec2 texturePosition;
out vec4 fragmentColor;

uniform sampler2D text;
uniform vec4 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texturePosition).r);
    fragmentColor = textColor * sampled;
}