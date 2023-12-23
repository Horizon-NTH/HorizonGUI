#version 330 core
in vec2 texturePosition;
out vec4 fragmentColor;

uniform sampler2D button;
uniform vec4 buttonColor;

uniform int focused;
uniform bool custom;

void main()
{
    if (!custom)
    {
        fragmentColor = vec4(buttonColor);
    }
    else
    {
        fragmentColor = vec4(buttonColor) * texture(button, texturePosition);
    }
    if (focused == 1)
    {
        if (fragmentColor.w < 1)
        {
            float luminance = 0.2126 * fragmentColor.r + 0.7152 * fragmentColor.g + 0.0722 * fragmentColor.b;
            if (luminance > 0.5)
                fragmentColor = vec4(vec3(1.0), 0.05);
            else  
                fragmentColor = vec4(vec3(0.0), 0.05);
        }
        else
        {
            if (all(greaterThan(fragmentColor.xyz, vec3(0.1))))
                fragmentColor.xyz *= 0.9;
            else
                fragmentColor.xyz += 0.1;
        }

    }
    else if (focused == 2)
    {
        if (fragmentColor.w < 1)
        {
            float luminance = 0.2126 * fragmentColor.r + 0.7152 * fragmentColor.g + 0.0722 * fragmentColor.b;
            if (luminance > 0.5)
                fragmentColor = vec4(vec3(1.0), 0.1);
            else  
                fragmentColor = vec4(vec3(0.0), 0.1);
        }
        else
        {
            if (all(greaterThan(fragmentColor.xyz, vec3(0.1))))
                fragmentColor.xyz *= 0.8;
            else
                fragmentColor.xyz += 0.2;
        }
    }
}
