#version 400
layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;

uniform mat4 MVP;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldNormal;
out vec3 worldPosition;

void main () {
      gl_Position = projectionMatrix * viewMatrix * MVP * vec4(vp, 1.0);
      //
      worldNormal = (transpose(inverse(mat3(MVP))) * normal);
      worldPosition = vec3(MVP * vec4(vp, 1.0));
}