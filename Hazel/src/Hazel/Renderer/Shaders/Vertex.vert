#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Transform;

out vec4 color;

void main()
{
	color		= aColor;
	gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(aPos, 1.0);
}