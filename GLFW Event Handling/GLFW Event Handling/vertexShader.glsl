#version 400
in layout(location=0) vec3 position;
in layout(location=1) vec3 color;
in layout(location=2) vec2 uv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 oColor;
void main(){
	gl_Position = projection * view * model * vec4(position, 1.0);
	oColor = vec4(color, 1.0);
}