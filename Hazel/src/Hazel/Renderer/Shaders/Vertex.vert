#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 u_ViewProjectionMatrix;

out vec4 color;

void main()
{
	color = aColor;
	gl_Position = u_ViewProjectionMatrix * vec4(aPos, 1.0);
}