#version 440 core

in vec2 textureCoord;

out vec4 fragColor;

uniform vec4 u_Color;
uniform sampler2D u_Diffuse;

void main()
{
	fragColor = texture(u_Diffuse, textureCoord) + u_Color*0;
}