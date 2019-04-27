#version 400
//out vec4 frag_colour;
in vec3 Color;
void main () {
  gl_FragColor = vec4(Color, 1.0);
}