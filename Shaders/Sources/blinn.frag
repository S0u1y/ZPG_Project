#version 400
out vec4 frag_colour;
in vec3 worldNormal;
in vec4 worldPosition;

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

float getIntensity(float p_a, float p_b){

      vec3 lightVec = lightPosition - vec3(worldPosition);
      float distance = length(lightVec);

      return 1 / (p_a * distance * distance + p_b * distance * 1);
}

void main () {
      vec4 ambient = vec4(0.01, .1, .1, 1);

      vec3 lightDirection = normalize(lightPosition - vec3(worldPosition));
      float s = dot(lightDirection, normalize(worldNormal));
      float diff = max(s, 0.0);
      vec3 viewDirection = normalize(cameraPosition - vec3(worldPosition));
      vec3 reflectDir = reflect ( -lightDirection , normalize(worldNormal) );
      vec3 halfwayDir = normalize(lightDirection + cameraPosition);
      float spec = pow ( max ( dot ( halfwayDir , reflectDir ), 0.0) ,32);

      float specularStrength = 0.5;
      vec4 specular = vec4(0);
      if(s > 0){
            specular = vec4(spec * specularStrength);// * vec4(1,0,1,1) ;
      }

      vec4 diffuse = diff * vec4(lightColor, 1);

      float intensity = getIntensity(a, b);

      frag_colour =( ambient + (diffuse + specular) * intensity) * vec4(objectColor, 1) ;

}