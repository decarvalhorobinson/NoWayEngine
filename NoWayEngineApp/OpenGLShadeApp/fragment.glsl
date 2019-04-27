#version 400

uniform vec3 lightDirection;

varying vec3 normal;

// Interpolated values from the vertex shaders
in vec2 uv;

// Ouput data
//out vec3 color;


uniform sampler2D sampler;

void main(void) {

	vec3 _normal = normalize(normal);	
	float kd = dot(_normal, - lightDirection);	
	vec4 normal_light_color = vec4(kd, kd, kd, 1.0);
	gl_FragColor = texture(sampler, uv) * normal_light_color;
}
