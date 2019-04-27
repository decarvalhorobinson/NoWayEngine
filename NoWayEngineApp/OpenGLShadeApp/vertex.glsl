#version 400
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

attribute vec4 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexTexCoord;

varying vec3 normal;

// Output data ; will be interpolated for each fragment.
out vec2 uv;

void main(void) {

	normal = normalMatrix * vertexNormal;
	gl_Position = projectionMatrix * modelViewMatrix * vertexPosition;
	uv = vertexTexCoord;
}