#version 400
in vec3 VertexPosition;
uniform vec3 VertexColor;

uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

out vec3 Color;

void main()
{
    Color = VertexColor;

    gl_Position = MVP * vec4(VertexPosition, 1.0f);
}