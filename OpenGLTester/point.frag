#version 400
layout (location = 0) out vec4 fragment;
uniform sampler2D tex;
in vec2 TexCode;
void main()
{
 fragment = vec4(1.0,0.0,0.0,1.0);
}