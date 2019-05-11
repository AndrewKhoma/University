#version 450 core

out vec4 frag_color;

uniform vec3 input_color;

void main() {
    frag_color = vec4(input_color, 1.0);
}