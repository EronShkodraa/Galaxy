#version 330 core
in vec3 starColor;
in float brightness;

out vec4 FragColor;

void main() {
    vec2 center = gl_PointCoord - vec2(0.5);
    float dist = length(center);
    
    if (dist > 0.5) discard;
    
    float glow = 1.0 - dist * 2.0;
    glow = pow(glow, 0.8);
    
    vec3 color = starColor * brightness * glow;
    float alpha = glow * brightness;
    
    FragColor = vec4(color, alpha);
}