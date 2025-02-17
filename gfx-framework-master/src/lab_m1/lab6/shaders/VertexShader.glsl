#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0)  in vec3 v_poz;
layout(location = 3) in vec3 v_norm;
layout(location = 2) in vec2 texture;
layout(location = 1) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float eTime;

out vec3 frag_norm;
out vec2 frag_text;
out vec3 frag_col;

// Output
// TODO(student): Output values to fragment shader
int state = 0;
void main()
{

    //vec3 v_new = v_poz;
    //v_new.y += sin(eTime + v_poz.x) * 0.5;

    //vec3 new_col = v_color;
    //new_col.r = sin(eTime);
    //new_col.b = cos(eTime + v_color.b);
   // new_col.g = sin(eTime) - cos(eTime + v_color.g);
     

    frag_norm = v_norm;
    frag_text = texture;
    frag_col = v_color;
    // TODO(student): Send output to fragment shader

    // TODO(student): Compute gl_Position
   gl_Position = Projection * View * Model * vec4(v_poz, 1.0);

}
