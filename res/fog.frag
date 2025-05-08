#version 400

out vec4 FragColor;


in vec4 v_pos; 
vec3 fogColor = vec3(0.5,0.5,0.5); //set this to the background colour from your application


float maxDist = 10.0f; //fog max distance
float minDist = 0.0f; //fog min distance


void main() 
{
float dist = abs( v_pos.z ); //return the absolute value (i.e positive z position)
float fogFactor = ((maxDist - dist)/(maxDist-minDist));
fogFactor = clamp( fogFactor, 0.0, 1.0 ); // clamp between 0 and 1
vec3 lightColor = vec3(0.1,0.1,0.1);
vec3 color = mix( fogColor, lightColor, 1-fogFactor);


FragColor = vec4(color, 1.0);
}
