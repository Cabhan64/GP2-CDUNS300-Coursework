#version 400

in vec3 normal;          // Normal in view space (from vertex shader)
in vec3 viewDirection;   // View direction in view space (from vertex shader)
in vec2 texCoords;       // Texture coordinates passed from vertex shader

uniform vec3 rimColor;    // Rim light color (from uniform)
uniform sampler2D textureSampler; // Texture sample

out vec4 fragColor;  

void main()
{
    
    vec3 norm = normalize(normal);      
    vec3 viewDir = normalize(viewDirection);

    float rim = 1.0 - max(dot(norm, viewDir), 0.0); 
    rim = smoothstep(0.7, 1.0, rim);  

    // Sample the texture color
    vec3 color = texture(textureSampler, texCoords).rgb;

    // Default ambient light (dim white color)
    vec3 ambientColor = vec3(0.5, 0.1, 0.1);  // Dim white light (low intensity)

    // Combine ambient light with the rim lighting effect
    vec3 finalColor = color * ambientColor;  // Ambient light contribution

    // Apply rim lighting effect (using rimColor instead of lightColor)
    finalColor += (rim*2 * rimColor);  // Use rimColor for the rim lighting effect

    // Output the final color
    gl_FragColor = vec4(finalColor, 1.0);
}
