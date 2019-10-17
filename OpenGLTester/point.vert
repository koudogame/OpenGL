#version 400
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 texcode;
layout (location = 2) in vec3 nomal;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 position;

out vec2 TexCode;
void main()
{
 mat4 model_view = view * position;
 gl_Position = projection * model_view * vec4(vertex_position,1.0F);
 TexCode = texcode;
}