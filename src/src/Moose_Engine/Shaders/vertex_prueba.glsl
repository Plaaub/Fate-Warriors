#version 450 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Position;    //VERTICES EN COORDENADAS DE VISTA
out vec3 Normal;      //NORMAL EN COORDENADAS DE VISTA

uniform mat4 modelView;
uniform mat4 normal;
uniform mat4 MVP;

void main()
{
    	//TRANSFORMAR VERTICE Y NORMAL A COORDENADAS DE VISTA
	Position = vec3 (modelView * aPos);
	Normal = vec3 (normalize (normal * aNormal));
    TexCoords = aTexCoords;    
    gl_Position = MVP * aPos;
}