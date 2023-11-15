#version 450

in vec3 worldPosition;

uniform samplerCube textureUnitID;

out vec4 frag_colour;


void main () {

    frag_colour = texture(textureUnitID, worldPosition);
}