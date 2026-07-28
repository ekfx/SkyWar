#version 330 core

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D TexSlot;  // Sampler2D 
uniform vec3 particleDot;   // particle pixels
uniform vec2 screenRes;     // for uv

void main() {
    /*
        ------------------------------------------
        Normalization -> vec2 uv = ((gl_FragCoord.xy * 2.0) - screenRes.xy) / screenRes.y;:
        current_position_in_screen(500, 400) -> gl_FragCoord -> vec2
        screenRes(1920,1080)                 -> Screen Resolution -> vec2 (uniform)

        ------------------------------------------
        X Axis -> Substitution Values
        ((500 * 2) - 1920) / 1080
        (1000 - 1920) / 1080
        -920 / 1080
        -0.85

        ------------------------------------------
        Y Axis -> Substitution Values
        ((400 * 2) - 1920) / 1080
        (800 - 1920) / 1080
        -1120 / 1080
        -1.03

        uv = vec2(-0.85, -1.03)
    */
    vec2 uv = ((gl_FragCoord.xy * 2.0) - screenRes.xy) / screenRes.y;
    
    // Radius
    float radius = 0.025; // -> means the minimum distance;
    float dist = distance(uv.xy, particleDot.xy);
    float blur = radius - dist;
    float blurStregth = 55; // less means more blur

    if (dist < radius) {
        /*
            it means: if we are less than 0.01 distance from
                      particle dot, paint it white. I think it's 
                      like length();

            The "blur" I did here is about getting the max
            value (radius) and subtracting by the current
            distance of our pixel and the pixel target;

            after that we get this difference and multiply
            many times to increase the effect starting from zero.
        */
        float color = (0.0 + (blur * blurStregth));
        //FragColor = vec4(0.0 + (blur * blurStregth));
        FragColor = vec4(color, color * 0.25, 0.0, color);
    } else {
        FragColor = texture(TexSlot, vec2(TexCoord.x, TexCoord.y));
    }
}