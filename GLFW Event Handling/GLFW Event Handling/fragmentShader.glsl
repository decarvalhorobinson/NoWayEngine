#version 400

out vec4 outputColor;

in vec4 oColor; 

void main(){
	outputColor = oColor;
	//outputColor = vec4(1.0, 0.0, 0.0, 0.0);
	}