#version 400

in vec3 normal;
in vec3 viewDirection;
in vec2 texCoords;

out vec4 fragmentColour;

uniform sampler2D diffuse;
uniform sampler2D plaid;


void main() {
    vec4 base_col = texture2D(diffuse,texCoords );
    vec4 plaid_col = texture2D( plaid, fract( texCoords / vec2(32.0) ) );
    gl_FragColor = base_col*plaid_col;
        //gl_FragCoord.xy/screensize;
}