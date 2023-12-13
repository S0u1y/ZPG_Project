#version 450

in vec2 vt_out;

uniform sampler2D textureUnitID;

uniform vec3 objectColor;

out vec4 frag_colour;

void main () {
    frag_colour = texture(textureUnitID, vt_out) * vec4(objectColor, 1);
}