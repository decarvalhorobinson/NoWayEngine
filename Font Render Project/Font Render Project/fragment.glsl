#version 400

out vec4 outputColor;

in vec4 oColor; 
uniform sampler2D text;
in vec2 uv;

void main(){
	//outputColor =  vec4(texture(text,uv).a,0,0,1);
	//outputColor = vec4(1.0, 0.0, 0.0, 0.0);
	float u_buffer = 0.45;
	float u_gamma = 0.005;
	vec4 u_color = vec4(1,1,0, 1);
	//u_color =  texture(text,uv);
	//outputColor = u_color;
	float dist = texture2D(text, uv).a;
    float alpha = smoothstep(u_buffer - u_gamma, u_buffer + u_gamma, dist);
    outputColor = vec4(u_color.rgb, alpha * u_color.a);
	


	}