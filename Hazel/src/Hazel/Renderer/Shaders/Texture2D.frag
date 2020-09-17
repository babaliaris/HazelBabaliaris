#version 440 core

in vec2 textCoord;

out vec4 fragColor;

uniform sampler2D u_Diffuse;

void main()
{
	fragColor = texture(u_Diffuse, textCoord);
}