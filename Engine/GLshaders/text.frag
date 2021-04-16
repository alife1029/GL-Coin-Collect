#version 330 core

in vec2 v_TexCoords;

uniform sampler2D text;
uniform vec4 u_TextColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, v_TexCoords).r);
	gl_FragColor = u_TextColor * sampled;
}