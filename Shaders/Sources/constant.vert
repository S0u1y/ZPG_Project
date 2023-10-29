#version 400
layout(location=0) in vec4 vp;
layout(location=1) in vec4 normal;

uniform mat4 MVP;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
      gl_Position = projectionMatrix * viewMatrix * MVP * vp;
}