#version 330 core

layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;

out vec4 fragmentColor;

uniform vec2 canvasPosition;
uniform vec2 canvasSize;
uniform float canvasRotation;
uniform vec2 center;
uniform vec4 color;
uniform float radius;
uniform bool circle;

bool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point);
vec2 rotate(const vec2 point, const vec2 center, const float theta);

void main()
{
    vec2 pixelCoords = gl_FragCoord.xy,
    centerCanvas = canvasPosition + canvasSize / 2.0;

    if (is_in_rectangle(rotate(canvasPosition, centerCanvas, canvasRotation), rotate(canvasPosition + vec2(canvasSize.x, 0.0), centerCanvas, canvasRotation),
    rotate(canvasPosition - vec2(0.0, canvasSize.y), centerCanvas, canvasRotation), pixelCoords) ||
    (circle && distance(pixelCoords, center) > radius))
    {
        discard;
    }
    fragmentColor = color;
}

bool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point)
{
    float dotAMAB = dot(point - A, B - A), dotAMAD = dot(point - A, D - A);
    return (0.0 < dotAMAB && dotAMAB < dot(B - A, B - A)) && (0.0 < dotAMAD && dotAMAD < dot(D - A, D - A));
}

vec2 rotate(const vec2 point, const vec2 center, const float theta)
{
    vec2 translated = point - center;

    float angleRadians = radians(theta);
    float cosTheta = cos(angleRadians);
    float sinTheta = sin(angleRadians);

    vec2 rotated = vec2(translated.x * cosTheta - translated.y * sinTheta, translated.x * sinTheta + translated.y * cosTheta);

    return rotated + center;
}
