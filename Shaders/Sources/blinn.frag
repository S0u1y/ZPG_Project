#version 400
out vec4 frag_colour;
in vec3 worldNormal;
in vec3 worldPosition;

uniform vec3 cameraPosition;

//light source variables
struct lightSource{
      vec3 lightPosition;
      vec3 lightVector;
      float lightAngle;

      vec3 lightColor;
      float a;
      float b;
      float k;
};
uniform int lightSources_n;
uniform lightSource lightSources[5];

//object variables
uniform vec3 objectColor;

uniform float r_a;
uniform float r_d;
uniform float r_s;

float getIntensity(float p_k, float p_a, float p_b){

      vec3 lightVec = lightPosition - worldPosition;
      float distance = length(lightVec);

      return 1 / (p_k + p_a * distance * distance + p_b * distance * 1);
}

void main () {
      vec4 ambient = vec4(0.01, .1, .1, 1);

      vec4 diffuse_final = vec4(0);
      vec4 specular_final = vec4(0);

      for(int i = 0; i < lightSources_n && i < 5; i++){
            vec3 lightDirection = normalize(lightSources[i].lightPosition - vec3(worldPosition));
            float s = dot(lightDirection, normalize(worldNormal));
            float diff = max(s, 0.0);
            vec3 viewDirection = normalize(cameraPosition - vec3(worldPosition));
            vec3 reflectDir = reflect ( -lightDirection , normalize(worldNormal) );
            vec3 halfwayDir = normalize(lightDirection + viewDirection);
            float spec = pow ( max ( dot ( normalize(worldNormal), halfwayDir ), 0.0) ,32);

            float specularStrength = 0.5;
            vec4 specular = vec4(0);
            if(s > 0){
                  specular = vec4(spec * specularStrength);// * vec4(1,0,1,1) ;
            }

            float intensity = 1;//getIntensity(k, a, b);
            vec4 diffuse = diff * vec4(lightColor, 1) * intensity;
            specular *= intensity;

            specular_final += specular;
            diffuse_final += diffuse;
      }

      frag_colour =( ambient + diffuse_final + specular_final) * vec4(objectColor, 1) ;

}