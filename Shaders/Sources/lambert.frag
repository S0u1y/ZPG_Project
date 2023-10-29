#version 400
out vec4 frag_colour;
in vec3 worldNormal;
in vec4 worldPosition;

//light source variables
uniform vec3 lightPosition;
uniform vec3 lightVector;
uniform float lightAngle;

uniform vec3 lightColor;
uniform float a;
uniform float b;

//object variables
uniform vec3 objectColor;

float getIntensity(float p_a, float p_b){

      vec3 lightVec = lightPosition - vec3(worldPosition);
      float distance = length(lightVec);

      return 1 / (p_a * distance * distance + p_b * distance * 1);
}

void main () {

      vec3 lightDirection = lightPosition - vec3(worldPosition);
      float diff = 0;
      diff = max(dot(normalize(lightDirection), normalize(worldNormal)), 0.0);
//spotlight
//      float angle = dot(normalize(vec3(worldPosition) - lightPosition), normalize(lightVector));
//      float inten = clamp(angle, 0, 1);
      float inten = getIntensity(a, b);;

      vec4 ambient = vec4(.1,0.1,0.1,1.0);
      vec4 diffuse = vec4(diff * lightColor, 1);


      frag_colour = ( ambient + diffuse * inten) * vec4(objectColor, 1);
}