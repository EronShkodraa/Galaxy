#version 330 core
in vec3 nebulaColor;
in float alpha;

out vec4 FragColor;

void main() {
    vec2 center = gl_PointCoord - vec2(0.5);
    float dist = length(center);
    
    if (dist > 0.5) discard;
    
    float glow = 1.0 - dist * 2.0;
    glow = pow(glow, 2.5);
    
    float softGlow = exp(-dist * 6.0);
    
    float finalAlpha = alpha * (glow * 0.6 + softGlow * 0.4);
    
    FragColor = vec4(nebulaColor, finalAlpha);
}