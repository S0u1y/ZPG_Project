#version 400
out vec4 frag_colour;
in vec3 worldNormal;
in vec3 worldPosition;

uniform vec3 cameraPosition;

//light source variables
uniform vec3 lightPosition;
uniform vec3 lightVector;
uniform float lightAngle;

uniform vec3 lightColor;
uniform float a;
uniform float b;

//object variables
uniform vec3 objectColor;

uniform float r_a;
uniform float r_d;
uniform float r_s;

float getIntensity(float p_a, float p_b){

      vec3 lightVec = lightPosition - worldPosition;
      float distance = length(lightVec);

      return 1 / (p_a * distance * distance + p_b * distance * 1);
}

void main () {
      vec3 lightDirection = normalize(lightPosition - worldPosition);
      float diff = max(dot(lightDirection, normalize(worldNormal)), 0.0);
      vec3 viewDirection = normalize(cameraPosition - worldPosition);
      vec3 reflectionDirection = reflect(-lightDirection, normalize(worldNormal));

      vec4 ambient = vec4(0.01, 0.1, 0.1, 1.0) * r_a;
      vec4 diffuse = (diff * r_d) * vec4(lightColor, 1);
      float intensity = getIntensity(a, b);

      float specularLight = 0.5f;

      float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 1);
      vec4 specular = vec4(specAmount * r_s * specularLight) * vec4(lightColor, 1);
//      if(diff == 0){
//            specular = 0;
//      }
      if(dot(lightDirection, worldNormal) < 0){
            specular = vec4(0);
      }

      frag_colour = ( ambient + diffuse * intensity + specular * intensity)* vec4(objectColor, 1) ;
}