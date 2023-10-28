#version 400
out vec4 frag_colour;
in vec3 worldNormal;
in vec4 worldPosition;

uniform vec3 cameraPosition;
void main () {
      vec3 lightPosition = vec3(0,0,0);
      vec3 lightVector = vec3(0,10,0);
      vec3 lightDirection = normalize(lightPosition - vec3(worldPosition));
      float diff = max(dot(normalize(lightPosition - vec3(worldPosition)), normalize(worldNormal)), 0.0);

      vec3 halfwayDir = normalize ( lightDirection + cameraPosition );
      float specularLight = 0.50f;
      vec3 reflectionDirection = reflect(-lightDirection, worldNormal);
      vec3 viewDirection = normalize(cameraPosition - vec3(worldPosition));
      float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
      vec3 specular = lightDirection * reflectionDirection * max((worldNormal * halfwayDir), 0);




      vec4 ambient = vec4(0.01, 0.1, 0.1, 1.0);
      vec4 diffuse = diff * vec4(1, 1, 1, 1);


      vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);
      frag_colour = ( ambient + diffuse + vec4(specular,1) )* objectColor ;
}