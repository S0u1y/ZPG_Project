#version 400
out vec4 frag_colour;
in vec3 worldNormal;
in vec4 worldPosition;

//light source variables
uniform vec3 lightPosition;
uniform vec3 lightVector;
uniform float lightAngle;

uniform vec3 lightColor;

//object variables
uniform vec3 objectColor;

void main () {

      vec3 lightDirection = lightPosition - vec3(worldPosition);
      float diff = 0;
      diff = max(dot(normalize(lightDirection), normalize(worldNormal)), 0.0);

      float angle = dot(normalize(vec3(worldPosition) - lightPosition), normalize(lightVector));
      float inten = clamp(angle, 0, 1);

      vec4 ambient = vec4(.1,0.1,0.1,1.0);
      vec4 diffuse = vec4(diff * lightColor, 1);

      frag_colour = ( ambient + diffuse * inten) * vec4(objectColor, 1);
}