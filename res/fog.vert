#version 400

layout (location = 0) in vec3 VertexPosition;

uniform mat4 transform;

attribute vec2 texCoord;

varying vec2 texCoord0;

out vec4 v_pos; 

void main()
{
	v_pos = transform * vec4(VertexPosition, 1.0);
	gl_Position = transform * vec4(VertexPosition, 1.0);
	texCoord0 = texCoord;
}

