#pragma once
class Shader
{
private:
	Shader();
	Shader(const Shader&) = delete;
	Shader& operator= (const Shader&) = delete;
public:
	inline static Shader* Get() { static Shader instance; return &instance; }
public:
	~Shader();

public:
	GLuint loadProgram(std::string VertexShaderSourceName, std::string FragmentShaderSourceName);

private:
	GLuint createProgram(const GLchar* VertexSource, const GLchar* FragmentSource);;
	GLboolean printShaderInfoLog(GLuint ShaderObj, const GLchar* Str);
	GLboolean printProgramInfoLog(GLuint ProgramObj);
	GLboolean readSource(const std::string& SourceName, std::vector<GLchar>& Buffer);
};

