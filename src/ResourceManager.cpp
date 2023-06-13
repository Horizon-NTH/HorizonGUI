#include <hgui/header/ResourceManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Shader>> hgui::ResourceManager::m_shaders;
std::map<std::string, std::shared_ptr<hgui::kernel::Texture>> hgui::ResourceManager::m_textures;
std::map<std::string, std::string> hgui::ResourceManager::m_glsl =
{
	{"VertexShaderText.glsl",
R"(
#version 330 core

layout (location = 0) in vec4 vertex;
out vec2 texturePosition;

uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * vec4(vertex.xy, 0.0, 1.0);
    texturePosition = vertex.zw;
}
)"},
    {"FragmentShaderText.glsl",
R"(
#version 330 core

in vec2 texturePosition;
out vec4 fragmentColor;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texturePosition).r);
    fragmentColor = vec4(textColor, 1.0) * sampled;
}
)"},
	{"VertexShaderSprites.glsl",
R"(
#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 texturePosition;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    texturePosition = vertex.zw;
    gl_Position = projectionMatrix * modelMatrix * vec4(vertex.xy, 0.0, 1.0);
}
)"},
    {"FragmentShaderSprites.glsl",
R"(
#version 330 core

in vec2 texturePosition;
out vec4 fragmentColor;

uniform sampler2D sprite;
uniform vec3 spriteColor;

void main()
{
    fragmentColor = vec4(spriteColor, 1.0) * texture(sprite, texturePosition);
    if (fragmentColor.w < 1)
        discard;
}
)"},
	{"VertexShaderFrameBuffer.glsl",
R"(
#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 texturePosition;

void main()
{
    texturePosition = vertex.zw;
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
}
)"},
	{"FragmentShaderFrameBuffer.glsl",
R"(
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
)"},
    { "VertexShaderButton.glsl",
R"(
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
)" },
    {"FragmentShaderButton.glsl",
R"(
#version 330 core
in vec2 texturePosition;
out vec4 fragmentColor;

uniform sampler2D button;
uniform vec3 buttonColor;
uniform vec3 backgroundColor;

uniform int focused;
uniform bool custom;


void main()
{
    if (!custom)
    {
        fragmentColor = vec4(buttonColor, 1.0);
    }
    else
    {
        fragmentColor = vec4(buttonColor, 1.0) * texture(button, texturePosition);
    }

    if (focused == 0)
    {

    }
    else if (focused == 1)
    {
        if (fragmentColor.w < 1)
        {
            fragmentColor = vec4(backgroundColor, 0.1);
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
            fragmentColor = vec4(backgroundColor, 0.2);
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
)"},
    {"VertexShaderCanva.glsl",
R"(
#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec3 vertexColor;

out vec3 color;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * modelMatrix * vec4(vertex, 0.0, 1.0);
    color = vertexColor;
}
)"
    },
        { "FragmentShaderCanva.glsl",
R"(
#version 330 core

layout(origin_upper_left) in vec4 gl_FragCoord;

in vec3 color;

out vec4 fragmentColor;

uniform vec2 canvaPosition;
uniform vec2 canvaSize;

void main()
{
    if (gl_FragCoord.x < canvaPosition.x || gl_FragCoord.x > canvaPosition.x + canvaSize.x || 
            gl_FragCoord.y < canvaPosition.y || gl_FragCoord.y > canvaPosition.y + canvaSize.y)
    {
        discard;
    }
    else
    {
        fragmentColor = vec4(color, 1.0);
    }
}
)" }
};

std::shared_ptr<hgui::kernel::Shader>& hgui::ResourceManager::load_shader(const std::string& shaderName, const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode)
{
	if (m_shaders.find(shaderName) == m_shaders.end())
	{
		m_shaders[shaderName] = std::make_shared<kernel::Shader>(vertexShaderCode, fragmentShaderCode, geometryShaderCode);
		return m_shaders[shaderName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A SHADER WITH THE NAME : " + shaderName).c_str());
	}
}

std::shared_ptr<hgui::kernel::Shader>& hgui::ResourceManager::get_shader(const std::string& shaderName)
{
	if (m_shaders.find(shaderName) != m_shaders.end())
	{
		return m_shaders[shaderName];
	}
	else
	{
		throw std::exception(("THERE IS NO SHADER WITH THE NAME : " + shaderName).c_str());
	}
}

void hgui::ResourceManager::delete_shaders(std::initializer_list<std::string> shadersNames)
{
	if (shadersNames.size())
	{
		for (const std::string& str : shadersNames)
		{
			glDeleteProgram(m_shaders[str]->get_id());
			m_shaders.erase(str);
		}
	}
	else
	{
		for (auto it = m_shaders.begin(); it != m_shaders.end(); it++)
		{
			glDeleteProgram(it->second->get_id());
		}
		m_shaders.clear();
	}
}

std::shared_ptr<hgui::kernel::Texture>& hgui::ResourceManager::load_texture(const std::string& textureName, const std::shared_ptr<kernel::Image>& image)
{
	if (m_textures.find(textureName) == m_textures.end())
	{
		m_textures[textureName] = std::make_shared<kernel::Texture>(image);
		return m_textures[textureName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A TEXTURE WITH THE NAME : " + textureName).c_str());
	}
}

std::shared_ptr<hgui::kernel::Texture>& hgui::ResourceManager::get_texture(const std::string& textureName)
{
	if (m_textures.find(textureName) != m_textures.end())
	{
		return m_textures[textureName];
	}
	else
	{
		throw std::exception(("THERE IS NO TEXTURE WITH THE NAME : " + textureName).c_str());
	}
}

void hgui::ResourceManager::delete_textures(std::initializer_list<std::string> texturesnames)
{
	if (texturesnames.size())
	{
		for (const std::string& str : texturesnames)
		{
			m_textures.erase(str);
		}
	}
	else
	{
		m_textures.clear();
	}
}
