#version 330
out vec3 frag_colour;

uniform vec3 objectColor;

void main () {
    frag_colour = objectColor;
}