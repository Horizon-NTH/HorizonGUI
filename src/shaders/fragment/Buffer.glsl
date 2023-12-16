#version 330 core

out vec4 fragmentColor;

in vec2 texturePosition;

uniform sampler2D screenTexture;
uniform int type;

void main()
{
	if (type == 1)
	{
		const float offset = 1.0 / 300.0;
			vec2 offsets[9] = vec2[](
			vec2(-offset,  offset),
			vec2( 0.0f,    offset),
			vec2( offset,  offset),
			vec2(-offset,  0.0f),
			vec2( 0.0f,    0.0f),
			vec2( offset,  0.0f),
			vec2(-offset, -offset),
			vec2( 0.0f,   -offset),
			vec2( offset, -offset)
		);

		float kernel[9] = float[](
			1.0 / 16, 2.0 / 16, 1.0 / 16,
			2.0 / 16, 4.0 / 16, 2.0 / 16,
			1.0 / 16, 2.0 / 16, 1.0 / 16
		);

		vec3 sampleTex[9];
		for(int i = 0; i < 9; i++)
		{
			sampleTex[i] = vec3(texture(screenTexture, texturePosition.st + offsets[i]));
		}
		vec3 col = vec3(0.0);
		for(int i = 0; i < 9; i++)
			col += sampleTex[i] * kernel[i];
		fragmentColor = vec4(col, 1.0);
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