#version 330 core

out vec4 fragmentColor;

in vec2 texturePosition;

uniform sampler2D screenTexture;
uniform vec2 screenSize;
uniform int type;

void main()
{
    if (type == 1)
    {
        float squarredPi = 6.28318530718;

        float direction = 32.0;
        float quality = 8.0;
        float size = 16.0;

        vec2 radius = size/screenSize.xy;
        vec2 uv = gl_FragCoord.xy/screenSize.xy;
        vec4 color = texture(screenTexture, uv);

        for (float d=0.0; d<squarredPi; d+=squarredPi/direction)
        {
            for (float i=1.0/quality; i<1.001; i+=1.0/quality)
            {
                color += texture(screenTexture, uv+vec2(cos(d), sin(d))*radius*i);
            }
        }
        color /= quality * direction + 1.0;
        fragmentColor =  color;
    }
    else if (type == 2)
    {
        fragmentColor = vec4(vec3(1.0) - vec3(texture(screenTexture, texturePosition)), 1.0);
    }
    else
    {
        fragmentColor = vec4(vec3(texture(screenTexture, texturePosition)), 1.0);
    }
}