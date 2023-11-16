#version 450

layout(location=0) in vec3 vp;

uniform mat4 MVP;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldPosition;

uniform vec3 cameraPosition;

void main() {
    mat4 matice = MVP;
    matice[3] = vec4(cameraPosition, 1);

    gl_Position = projectionMatrix * viewMatrix * vec4(cameraPosition + vp, 1.0);
    worldPosition = vp;
}