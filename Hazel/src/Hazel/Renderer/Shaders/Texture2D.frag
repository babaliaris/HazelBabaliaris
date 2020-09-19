#version 440 core

in vec2 textCoord;

out vec4 fragColor;

uniform sampler2D u_Diffuse;
uniform vec4 u_Color;
uniform float u_TilingFactor;

void main()
{
	fragColor = texture(u_Diffuse, textCoord * u_TilingFactor) * u_Color;
}