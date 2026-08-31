#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in float aSize;
layout (location = 3) in float aBrightness;

out vec3 starColor;
out float brightness;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_PointSize = aSize * (300.0f / gl_Position.w);
    starColor = aColor;
    brightness = aBrightness;
}