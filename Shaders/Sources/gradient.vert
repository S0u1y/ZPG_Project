#version 400
layout(location=0) in vec4 vp;
layout(location=1) in vec4 normal;

vec3 colorA = vec3(0.9,0.141,0.149);
vec3 colorB = vec3(1.000,0.833,0.224);

out vec4 color;
uniform mat4 MVP;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float time;

void main () {
      gl_Position = projectionMatrix * viewMatrix * MVP * vp;
      float pct = abs(sin(time));
      color = mix(vec4(colorA, 1), vec4(colorB, 1), pct);
}