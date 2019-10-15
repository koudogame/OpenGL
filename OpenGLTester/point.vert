#version 400
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 texcode;
layout (location = 2) in vec3 nomal;

out vec2 TexCode;
void main()
{
 gl_Position = vec4(vertex_position,1.0F);
 TexCode = texcode;
}