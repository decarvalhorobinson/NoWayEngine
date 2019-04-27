#version 400
in layout(location=0) vec3 position;
in layout(location=1) vec3 color;
in layout(location=2) vec2 uv2;
uniform mat4 mvp;
uniform int cursorPosition;
out vec2 uv;
out vec4 oColor;
void main(){
	gl_Position = mvp * vec4(position, 1.0);
	oColor = vec4(color, 1.0);
	uv = uv2;
}