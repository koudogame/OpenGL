#version 400
layout (location = 0) out vec4 fragment;
uniform sampler2D tex;

in vec3 Idiff;
in vec3 ISpecular;
in vec2 TexCode;
in vec3 LColor;
void main()
{
 fragment = texture(tex,TexCode) * vec4(Idiff + ISpecular,1.0) * vec4(LColor,1.0);
}