#version 430

in vec3 color;
in float heightDrone;

layout(location = 0) out vec4 out_color;

void main()
{
    vec3 color_darker = color * 0.5;
    float altitudeFactor = clamp(heightDrone / 120, 0.0, 1.0);
    vec3 color_new = mix(color,color_darker,altitudeFactor);
    out_color = vec4(color_new,1.0);
}
