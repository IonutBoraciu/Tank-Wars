#version 430
// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

layout(std430, binding = 0) buffer HeightBuffer {
    float heights[];
} heightBuffer;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float maxDrone;
uniform int type;

out vec3 color;
out float heightDrone;

float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f*f*(3.0-2.0*f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main()
{
    heightDrone = maxDrone;
    if(type == 1) {
      vec2 st =  v_position.xz * 0.05;
      vec2 pos2 = vec2(st);
      float n = noise(pos2);
      vec3 newPos = v_position;
      vec3 green = vec3(0.09,0.69,0.41);
      vec3 brown = vec3(0.36,0.25,0.2);
      color = mix(green,brown,n);
      newPos.y += n * 10;
      heightBuffer.heights[gl_VertexID] = newPos.y;
      gl_Position = Projection * View * Model * vec4(newPos, 1.0);
     } else {
       color = v_color;
       gl_Position = Projection * View * Model * vec4(v_position, 1.0);
     }
}
