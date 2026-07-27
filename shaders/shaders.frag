#version 330 core

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D TexSlot;  
uniform vec4 pColor;
uniform vec3 particleDot;
uniform vec2 screenRes;

void main() {
    vec2 uv = (gl_FragCoord.xy * 2.0 - screenRes.xy) / screenRes.y;
    // FragColor = pColor;
    if (distance(uv.xy, particleDot.xy) < 0.00001) {
        FragColor = vec4(1.0);
    } else {
        FragColor = texture(TexSlot, vec2(TexCoord.x, TexCoord.y));
    }
}