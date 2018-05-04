#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 TexCoord;

void main()
{
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	gl_Position = vec4(aPos, 1.0);
}