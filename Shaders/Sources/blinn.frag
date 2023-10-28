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

//object variables
uniform vec3 objectColor;


void main () {
      vec3 ambient = vec3(0.01, .1, .1);

      vec3 lightDirection = normalize(lightPosition - vec3(worldPosition));
      float s = dot ( worldNormal , lightDirection);
      float diff = max(s, 0.0);

      vec4 specular = vec4(0);
      if(s > 0){
            vec3 reflectDir = normalize(reflect ( -lightDirection , worldNormal ));
            vec3 viewDirection = normalize(cameraPosition - vec3(worldPosition));
            vec3 halfwayDir = normalize(lightDirection + viewDirection);
            float spec = pow ( max ( dot ( halfwayDir , reflectDir ), 0.0) ,32);
            float specularStrength = 0.5;

            specular = vec4(spec * specularStrength) * vec4(1,0,1,1) ;
      }

      frag_colour =( vec4(ambient, 1) + diff * vec4(lightColor, 1) + specular )* vec4(objectColor, 1) ;

}