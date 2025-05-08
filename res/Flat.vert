#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexNormal;

uniform mat4 transform;
uniform mat4 modelMatrix;
uniform vec3 camPos;


out vec3 normal;
out vec3 viewDirection;
out vec2 texCoords;
out vec2 v_vPosition;

void main() {

   vec4 worldPosition = transform * vec4(vertexPosition, 1.0);
   vec4 viewPosition = vec4(worldPosition.xyz - camPos, 1.0);

    texCoords = vertexUV;
    normal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
    viewDirection = -vec3(viewPosition);
    v_vPosition = vec2(vertexPosition); //important?
   
    
    gl_Position = transform * vec4((vertexPosition.x),0.0,(vertexPosition.z), 1.0);
     

}