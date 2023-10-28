#version 400
out vec4 frag_colour;
in vec3 worldNormal;
in vec4 worldPosition;
void main () {
      vec3 lightPosition = vec3(0,0,0);
      vec3 lightVector = vec3(0,10,0);
      float diff = max(dot(normalize(lightPosition - vec3(worldPosition)), normalize(worldNormal)), 0.0);
      vec4 ambient = vec4(0.01,0.1,0.1,1.0);
      vec4 diffuse = diff * vec4(1,1,1,1);
      vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);
      frag_colour = ( ambient + diffuse ) * objectColor ;
}