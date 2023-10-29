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

//object variables
uniform vec3 objectColor;

void main () {
      vec3 lightDirection = normalize(lightPosition - worldPosition);
      float diff = max(dot(normalize(lightPosition - worldPosition), worldNormal), 0.0);
      vec3 viewDirection = normalize(cameraPosition - worldPosition);
      vec3 reflectionDirection = reflect(-lightDirection, worldNormal);

      float specularLight = 0.50f;

      float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
      float specular = specAmount * specularLight;

      vec4 ambient = vec4(0.01, 0.1, 0.1, 1.0);
      vec4 diffuse = diff * vec4(1, 1, 1, 1);

      frag_colour = ( ambient + diffuse + specular )* vec4(objectColor, 1) ;
}