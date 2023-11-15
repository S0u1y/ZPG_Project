#version 450

layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform mat4 MVP;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldNormal;
out vec4 worldPosition;

out vec2 vt_out;

void main() {
    gl_Position = projectionMatrix * viewMatrix * MVP * vec4(vp, 1.0);
    worldNormal = transpose(inverse(mat3(MVP))) * normal;
    worldPosition = vec4(vp, 1);
    vt_out = uv;
}
