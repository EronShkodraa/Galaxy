#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in float aSize;
layout (location = 3) in float aAlpha;

out vec3 nebulaColor;
out float alpha;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_PointSize = aSize * (400.0f / gl_Position.w);
    nebulaColor = aColor;
    alpha = aAlpha;
}