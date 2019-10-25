#version 400
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 texcode;
layout (location = 2) in vec3 nomal;

uniform mat4 model_view;
uniform mat4 projection;
uniform mat3 nomal_matrix;

const vec4 LightPosition = vec4(0.0,0.0,10.0,1.0);
const vec3 LightColor = vec3(1,0.52,0);
const float Intensity = 6.08;
const vec3 LDiffuse = vec3(1.0);
const vec3 LSpecular = vec3(1.0);

const vec3 KDiffuse = vec3(0.8);
const vec3 KSpecular = vec3(0.0);
const vec3 KAnbient = vec3(0.0);

const float kShine = 30.0;

out vec2 TexCode;
out vec3 Idiff;
out vec3 ISpecular;
out vec3 LColor;
void main()
{
//Diffuse Light setup
 vec4 object_position =  model_view * vec4(vertex_position,1.0F);
 vec3 object_nomal = normalize(nomal_matrix * nomal);
 vec3 light = normalize((LightPosition * object_position.w - object_position * LightPosition.w).xyz);
 Idiff = max(dot(object_nomal,light),0) * LDiffuse * KDiffuse;

//Specular Light setup
 vec3 view_vector = -normalize(object_position.xyz);
 vec3 refrect_vector = reflect(-light,object_nomal);
 ISpecular = pow(max(dot(refrect_vector,view_vector),0.0),kShine) * KSpecular * LSpecular + KAnbient;
 LColor = LightColor * Intensity;

 gl_Position = projection * object_position;
 TexCode = texcode;
}