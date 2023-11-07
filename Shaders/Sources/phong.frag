#version 400
out vec4 frag_colour;
in vec3 worldNormal;
in vec3 worldPosition;

uniform vec3 cameraPosition;

//light source variables
struct lightSource{
      int type;
      vec3 lightPosition;
      vec3 lightVector;
      float lightAngle;

      vec3 lightColor;
      float linear;
      float quadratic;
      float constant;
};
uniform int lightSources_n;
uniform lightSource lightSources[5];

//object variables
uniform vec3 objectColor;

uniform float r_a;
uniform float r_d;
uniform float r_s;

float getIntensity(lightSource light){

      vec3 lightVec = light.lightPosition - worldPosition;
      float distance = length(lightVec);

      return 1 / (light.constant + light.quadratic * distance * distance + light.linear * distance * 1);
}

void main () {
      vec4 diffuse_final = vec4(0);
      vec4 specular_final = vec4(0);
      vec4 ambient = vec4(0.01, 0.1, 0.1, 1.0);

      for(int i = 0; i < lightSources_n; i++){

            vec3 lightDirection = normalize(lightSources[i].lightPosition - worldPosition);
            if ( lightSources[i].type == 2){
                  lightDirection = lightSources[i].lightVector;
            }

            if(lightSources[i].lightAngle != 360){
                  //spotlight

                  float alpha = radians(lightSources[i].lightAngle);
                  float angle = dot(-lightDirection, normalize(lightSources[i].lightVector));
                  float inten = (angle - cos(alpha))/(1 - cos(alpha));

                  if ( angle > cos(alpha)){//if we're inside the cone, then calculate the lighting...

                        float diff = max(dot(lightDirection, normalize(worldNormal)), 0.0);
                        vec3 viewDirection = normalize(cameraPosition - worldPosition);
                        vec3 reflectionDirection = reflect(-lightDirection, normalize(worldNormal));

                        vec4 diffuse = (diff * r_d) * vec4(lightSources[i].lightColor, 1);
                        float intensity = getIntensity(lightSources[i]);
                        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
                        vec4 specular = vec4(specAmount * r_s * 0.5f) * vec4(lightSources[i].lightColor, 1);
                        if(dot(lightDirection, worldNormal) < 0){
                              specular = vec4(0);
                        }

                        diffuse_final += diffuse * intensity * inten;
                        specular_final += specular * intensity * inten;

                  }
            }else{

                  float diff = max(dot(lightDirection, normalize(worldNormal)), 0.0);
                  vec3 viewDirection = normalize(cameraPosition - worldPosition);
                  vec3 reflectionDirection = reflect(-lightDirection, normalize(worldNormal));

                  vec4 diffuse = (diff * r_d) * vec4(lightSources[i].lightColor, 1);
                  float intensity = getIntensity(lightSources[i]);
                  float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
                  vec4 specular = vec4(specAmount * r_s * 0.5f) * vec4(lightSources[i].lightColor, 1);
                  if(dot(lightDirection, worldNormal) < 0){
                        specular = vec4(0);
                  }

                  diffuse_final += diffuse * intensity;
                  specular_final += specular * intensity;

            }

      }
//      diffuse_final = vec4(diffuse_final.x, diffuse_final.y, diffuse_final.z, 1);
//      specular_final = vec4(specular_final.x, specular_final.y, specular_final.z, 1);

      frag_colour = ( ambient + diffuse_final + specular_final )* vec4(objectColor, 1) ;
}