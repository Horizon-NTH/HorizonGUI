#version 330 core

layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;

out vec4 fragmentColor;

uniform vec2 canvasPosition;
uniform vec2 canvasSize;
uniform vec2 center;
uniform vec4 color;
uniform float radius;
uniform bool circle;

bool is_in_rectangle(const vec2 A, const vec2 B, const vec2 D, const vec2 point);

void main()
{
    vec2 pixelCoords = gl_FragCoord.xy;

    if (!is_in_rectangle(canvasPosition, canvasPosition + vec2(canvasSize.x, 0.0),
        canvasPosition + vec2(0.0, canvasSize.y), pixelCoords) ||
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