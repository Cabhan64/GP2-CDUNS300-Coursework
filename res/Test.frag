#version 400

in vec3 normal;
in vec3 viewDirection;
in vec2 texCoords;

out vec4 fragmentColour;

uniform vec3 rimColour;
uniform float rimPower;

uniform sampler2D diffuse;

float rimFactor;
float rimIntensity;

void main(){

    vec3 rimColourReal = vec3(0.5, 0.5, 0.5);

    vec3 N = normalize(normal);
    vec3 V = normalize(viewDirection);

    // Calculate rim factor with rimPower, then clamp it between 0.0 and 1.0
    rimFactor = clamp(1.0 - max(0.0, dot(N, V)), 0.0, 1.0);
    rimFactor = pow(rimFactor, rimPower);

    // Set rim intensity based on rimFactor
    if (rimFactor > 0.5) // or any other threshold you'd like
        rimIntensity = 1.0;
    else
        rimIntensity = 0.0;

    // Calculate the final fragment color, adding the rim effect
    vec4 baseColour = texture(diffuse, texCoords);
    fragmentColour = baseColour + vec4(rimColourReal, 1.0) * rimIntensity;
}
