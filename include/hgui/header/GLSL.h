#pragma once

#define HGUI_GLSL_VERTEX_CIRCLE "#version 330 core\nlayout (location = 0) in vec2 vertex;\nuniform mat4 projectionMatrix;\nvoid main()\n{\n	gl_Position = projectionMatrix * vec4(vertex, 0.0, 1.0);\n}"
#define HGUI_GLSL_VERTEX_RECTANGLE "#version 330 core\nlayout (location = 0) in vec2 vertex;\nuniform mat4 projectionMatrix;\nvoid main()\n{\n	gl_Position = projectionMatrix * vec4(vertex, 0.0, 1.0);\n}"
#define HGUI_GLSL_VERTEX_STRAIGHTLINE "#version 330 core\nlayout (location = 0) in vec2 vertex;\nuniform mat4 projectionMatrix;\nvoid main()\n{\n	gl_Position = projectionMatrix * vec4(vertex, 0.0, 1.0);\n}"
#define HGUI_GLSL_VERTEX_TRIANGLE "#version 330 core\nlayout (location = 0) in vec2 vertex;\nuniform mat4 projectionMatrix;\nvoid main()\n{\n	gl_Position = projectionMatrix * vec4(vertex, 0.0, 1.0);\n}"
#define HGUI_GLSL_VERTEX_SPRITE "#version 330 core\nlayout (location = 0) in vec4 vertex;\nout vec2 texturePosition;\nuniform mat4 modelMatrix;\nuniform mat4 projectionMatrix;\nvoid main()\n{\n    texturePosition = vertex.zw;\n    gl_Position = projectionMatrix * modelMatrix * vec4(vertex.xy, 0.0, 1.0);\n}"
#define HGUI_GLSL_VERTEX_BUTTON "#version 330 core\nlayout (location = 0) in vec4 vertex;\nout vec2 texturePosition;\nuniform mat4 modelMatrix;\nuniform mat4 projectionMatrix;\nvoid main()\n{\n    gl_Position = projectionMatrix * modelMatrix * vec4(vertex.xy, 0.0, 1.0);\n    texturePosition = vertex.zw;\n}"
#define HGUI_GLSL_VERTEX_CANVAS "#version 330 core\nlayout (location = 0) in vec2 vertex;\nlayout (location = 1) in vec3 vertexColor;\nout vec3 color;\nuniform mat4 modelMatrix;\nuniform mat4 projectionMatrix;\nvoid main()\n{\n    gl_Position = projectionMatrix * modelMatrix * vec4(vertex, 0.0, 1.0);\n    color = vertexColor;\n}"
#define HGUI_GLSL_VERTEX_LABEL "#version 330 core\nlayout (location = 0) in vec4 vertex;\nout vec2 texturePosition;\nuniform mat4 projectionMatrix;\nvoid main()\n{\n    gl_Position = projectionMatrix * vec4(vertex.xy, 0.0, 1.0);\n    texturePosition = vertex.zw;\n}"
#define HGUI_GLSL_VERTEX_BUFFER "#version 330 core\nlayout (location = 0) in vec4 vertex;\nout vec2 texturePosition;\nvoid main()\n{\n	texturePosition = vertex.zw;\n	gl_Position = vec4(vertex.xy, 0.0, 1.0);\n}"

#define HGUI_GLSL_FRAGMENT_CIRCLE "#version 330 core\nlayout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;\nout vec4 fragmentColor;\nuniform vec2 canvasPosition;\nuniform vec2 canvasSize;\nuniform float canvasRotation;\nuniform vec2 center;\nuniform vec3 color;\nuniform float radius;\nuniform float thickness;\nuniform bool fill;\nbool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point);\nvec2 rotate(const vec2 point, const vec2 center, const float theta);\nvoid main()\n{\n    vec2 pixelCoords = gl_FragCoord.xy,\n    centerCanvas = canvasPosition + canvasSize / 2.0;\n    if (is_in_rectangle(rotate(canvasPosition, centerCanvas, canvasRotation), rotate(canvasPosition + vec2(canvasSize.x, 0.0), centerCanvas, canvasRotation),\n    rotate(canvasPosition - vec2(0.0, canvasSize.y), centerCanvas, canvasRotation), pixelCoords)  ||\n    (fill && distance(pixelCoords, center) > radius) ||\n    (!fill && (distance(pixelCoords, center) > radius + thickness ||\n    distance(pixelCoords, center) < radius - thickness)))\n    {\n        discard;\n    }\n    fragmentColor = vec4(color, 1.0);\n}\nbool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point)\n{\n    float dotAMAB = dot(point - A, B - A), dotAMAD = dot(point - A, D - A);\n    return (0.0 < dotAMAB && dotAMAB < dot(B - A, B - A)) && (0.0 < dotAMAD && dotAMAD < dot(D - A, D - A));\n}\nvec2 rotate(const vec2 point, const vec2 center, const float theta)\n{\n    vec2 translated = point - center;\n    float angleRadians = radians(theta);\n    float cosTheta = cos(angleRadians);\n    float sinTheta = sin(angleRadians);\n    vec2 rotated = vec2(translated.x * cosTheta - translated.y * sinTheta, translated.x * sinTheta + translated.y * cosTheta);\n    return rotated + center;\n}"
#define HGUI_GLSL_FRAGMENT_RECTANGLE "#version 330 core\nlayout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;\nout vec4 fragmentColor;\nuniform vec2 canvasPosition;\nuniform vec2 canvasSize;\nuniform float canvasRotation;\nuniform vec2 center;\nuniform vec3 color;\nuniform float radius;\nuniform bool circle;\nbool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point);\nvec2 rotate(const vec2 point, const vec2 center, const float theta);\nvoid main()\n{\n    vec2 pixelCoords = gl_FragCoord.xy,\n			centerCanvas = canvasPosition + canvasSize / 2.0;\n    if (is_in_rectangle(rotate(canvasPosition, centerCanvas, canvasRotation), rotate(canvasPosition + vec2(canvasSize.x, 0.0), centerCanvas, canvasRotation), \n			rotate(canvasPosition - vec2(0.0, canvasSize.y), centerCanvas, canvasRotation), pixelCoords) ||\n		(circle && distance(pixelCoords, center) > radius))\n    {\n        discard;\n    } \n	fragmentColor = vec4(color, 1.0);\n}\nbool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point)\n{\n	float dotAMAB = dot(point - A, B - A), dotAMAD = dot(point - A, D - A);\n	return (0.0 < dotAMAB && dotAMAB < dot(B - A, B - A)) && (0.0 < dotAMAD && dotAMAD < dot(D - A, D - A));\n}\nvec2 rotate(const vec2 point, const vec2 center, const float theta)\n{\n	vec2 translated = point - center;\n	float angleRadians = radians(theta);\n	float cosTheta = cos(angleRadians);\n	float sinTheta = sin(angleRadians);\n	vec2 rotated = vec2(translated.x * cosTheta - translated.y * sinTheta, translated.x * sinTheta + translated.y * cosTheta);\n	return rotated + center;\n}"
#define HGUI_GLSL_FRAGMENT_STRAIGHTLINE "#version 330 core\nlayout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;\nout vec4 fragmentColor;\nuniform vec2 canvasPosition;\nuniform vec2 canvasSize;\nuniform float canvasRotation;\nuniform vec2 center;\nuniform vec3 color;\nuniform float radius;\nuniform bool circle;\nbool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point);\nvec2 rotate(const vec2 point, const vec2 center, const float theta);\nvoid main()\n{\n    vec2 pixelCoords = gl_FragCoord.xy,\n			centerCanvas = canvasPosition + canvasSize / 2.0;\n    if (is_in_rectangle(rotate(canvasPosition, centerCanvas, canvasRotation), rotate(canvasPosition + vec2(canvasSize.x, 0.0), centerCanvas, canvasRotation), \n			rotate(canvasPosition - vec2(0.0, canvasSize.y), centerCanvas, canvasRotation), pixelCoords) ||\n		(circle && distance(pixelCoords, center) > radius))\n    {\n        discard;\n    } \n	fragmentColor = vec4(color, 1.0);\n}\nbool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point)\n{\n	float dotAMAB = dot(point - A, B - A), dotAMAD = dot(point - A, D - A);\n	return (0.0 < dotAMAB && dotAMAB < dot(B - A, B - A)) && (0.0 < dotAMAD && dotAMAD < dot(D - A, D - A));\n}\nvec2 rotate(const vec2 point, const vec2 center, const float theta)\n{\n	vec2 translated = point - center;\n	float angleRadians = radians(theta);\n	float cosTheta = cos(angleRadians);\n	float sinTheta = sin(angleRadians);\n	vec2 rotated = vec2(translated.x * cosTheta - translated.y * sinTheta, translated.x * sinTheta + translated.y * cosTheta);\n	return rotated + center;\n}"
#define HGUI_GLSL_FRAGMENT_TRIANGLE "#version 330 core\nlayout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;\nout vec4 fragmentColor;\nuniform vec2 canvasPosition;\nuniform vec2 canvasSize;\nuniform float canvasRotation;\nuniform vec2 center;\nuniform vec3 color;\nuniform float radius;\nuniform bool circle;\nbool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point);\nvec2 rotate(const vec2 point, const vec2 center, const float theta);\nvoid main()\n{\n    vec2 pixelCoords = gl_FragCoord.xy,\n			centerCanvas = canvasPosition + canvasSize / 2.0;\n    if (is_in_rectangle(rotate(canvasPosition, centerCanvas, canvasRotation), rotate(canvasPosition + vec2(canvasSize.x, 0.0), centerCanvas, canvasRotation), \n			rotate(canvasPosition - vec2(0.0, canvasSize.y), centerCanvas, canvasRotation), pixelCoords) ||\n		(circle && distance(pixelCoords, center) > radius))\n    {\n        discard;\n    } \n	fragmentColor = vec4(color, 1.0);\n}\nbool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point)\n{\n	 float dotAMAB = dot(point - A, B - A), dotAMAD = dot(point - A, D - A);\n	return (0.0 < dotAMAB && dotAMAB < dot(B - A, B - A)) && (0.0 < dotAMAD && dotAMAD < dot(D - A, D - A));\n}\nvec2 rotate(const vec2 point, const vec2 center, const float theta)\n{\n	vec2 translated = point - center;\n	float angleRadians = radians(theta);\n	float cosTheta = cos(angleRadians);\n	float sinTheta = sin(angleRadians);\n	vec2 rotated = vec2(translated.x * cosTheta - translated.y * sinTheta, translated.x * sinTheta + translated.y * cosTheta);\n	return rotated + center;\n}"
#define HGUI_GLSL_FRAGMENT_SPRITE "#version 330 core\nin vec2 texturePosition;\nout vec4 fragmentColor;\nuniform sampler2D sprite;\nuniform vec4 spriteColor;\nvoid main()\n{\n    fragmentColor = vec4(spriteColor) * texture(sprite, texturePosition);\n    if (fragmentColor.w < 1)\n        discard;\n}"
#define HGUI_GLSL_FRAGMENT_BUTTON "#version 330 core\nin vec2 texturePosition;\nout vec4 fragmentColor;\nuniform sampler2D button;\nuniform vec4 buttonColor;\nuniform int focused;\nuniform bool custom;\nvoid main()\n{\n    if (!custom)\n    {\n        fragmentColor = vec4(buttonColor);\n    }\n    else\n    {\n        fragmentColor = vec4(buttonColor) * texture(button, texturePosition);\n    }\n    if (focused == 1)\n    {\n        if (fragmentColor.w < 1)\n        {\n            float luminance = 0.2126 * fragmentColor.r + 0.7152 * fragmentColor.g + 0.0722 * fragmentColor.b;\n            if (luminance > 0.5)\n                fragmentColor = vec4(vec3(1.0), 0.05);\n            else  \n                fragmentColor = vec4(vec3(0.0), 0.05);\n        }\n        else\n        {\n            if (all(greaterThan(fragmentColor.xyz, vec3(0.1))))\n                fragmentColor.xyz *= 0.9;\n            else\n                fragmentColor.xyz += 0.1;\n        }\n    }\n    else if (focused == 2)\n    {\n        if (fragmentColor.w < 1)\n        {\n            float luminance = 0.2126 * fragmentColor.r + 0.7152 * fragmentColor.g + 0.0722 * fragmentColor.b;\n            if (luminance > 0.5)\n                fragmentColor = vec4(vec3(1.0), 0.1);\n            else  \n                fragmentColor = vec4(vec3(0.0), 0.1);\n        }\n        else\n        {\n            if (all(greaterThan(fragmentColor.xyz, vec3(0.1))))\n                fragmentColor.xyz *= 0.8;\n            else\n                fragmentColor.xyz += 0.2;\n        }\n    }\n}"
#define HGUI_GLSL_FRAGMENT_CANVAS "#version 330 core\nin vec3 color;\nout vec4 fragmentColor;\nvoid main()\n{\n    fragmentColor = vec4(color, 1.0);\n}"
#define HGUI_GLSL_FRAGMENT_LABEL "#version 330 core\nin vec2 texturePosition;\nout vec4 fragmentColor;\nuniform sampler2D text;\nuniform vec4 textColor;\nvoid main()\n{\n    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texturePosition).r);\n    fragmentColor = vec4(textColor) * sampled;\n}"
#define HGUI_GLSL_FRAGMENT_BUFFER "#version 330 core\nout vec4 fragmentColor;\nin vec2 texturePosition;\nuniform sampler2D screenTexture;\nuniform int type;\nvoid main()\n{\n	if (type == 1)\n	{\n		const float offset = 1.0 / 300.0;\n			vec2 offsets[9] = vec2[](\n			vec2(-offset,  offset),\n			vec2( 0.0f,    offset),\n			vec2( offset,  offset),\n			vec2(-offset,  0.0f),\n			vec2( 0.0f,    0.0f),\n			vec2( offset,  0.0f),\n			vec2(-offset, -offset),\n			vec2( 0.0f,   -offset),\n			vec2( offset, -offset)\n		);\n		float kernel[9] = float[](\n			1.0 / 16, 2.0 / 16, 1.0 / 16,\n			2.0 / 16, 4.0 / 16, 2.0 / 16,\n			1.0 / 16, 2.0 / 16, 1.0 / 16\n		);\n		vec3 sampleTex[9];\n		for(int i = 0; i < 9; i++)\n		{\n			sampleTex[i] = vec3(texture(screenTexture, texturePosition.st + offsets[i]));\n		}\n		vec3 col = vec3(0.0);\n		for(int i = 0; i < 9; i++)\n			col += sampleTex[i] * kernel[i];\n		fragmentColor = vec4(col, 1.0);\n	}\n	else if (type == 2)\n	{\n		fragmentColor = vec4(vec3(1.0) - vec3(texture(screenTexture, texturePosition)), 1.0);\n	}\n	else\n	{\n		fragmentColor = vec4(vec3(texture(screenTexture, texturePosition)), 1.0);\n	}\n}"
