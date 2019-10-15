#include "stdafx.h"
#include "Shader.h"


Shader::Shader()
{
}


Shader::~Shader()
{
}

GLuint Shader::loadProgram(std::string VertexShaderSourceName, std::string FragmentShaderSourceName)
{
	//Shaderソースの読み込み
	std::vector<GLchar> vertex_buffer;
	GLboolean vertex_tester = readSource(VertexShaderSourceName, vertex_buffer);
	std::vector<GLchar> fragment_buffer;
	GLboolean fragment_tester = readSource(FragmentShaderSourceName, fragment_buffer);

	return vertex_tester && fragment_tester ? createProgram(vertex_buffer.data(), fragment_buffer.data()) : 0;
}

GLuint Shader::createProgram(const GLchar * VertexSource, const GLchar * FragmentSource)
{
	//Programオブジェクトの作成
	const GLuint program(glCreateProgram());
	//Vertex Shader オブジェクトの作成
	const GLuint vertex_obj(glCreateShader(GL_VERTEX_SHADER));
	//Sourceの実装
	glShaderSource(vertex_obj, 1, &VertexSource, nullptr);
	//Shaderのコンパイル
	glCompileShader(vertex_obj);
	if (printShaderInfoLog(vertex_obj, "Vertex Source"))
		glAttachShader(program, vertex_obj);
	//削除マークを付ける
	glDeleteShader(vertex_obj);

	//Fragment Shaderオブジェクトの作成
	const GLuint fragment_obj(glCreateShader(GL_FRAGMENT_SHADER));
	//Sourceの実装
	glShaderSource(fragment_obj, 1, &FragmentSource, nullptr);
	//コンパイル
	glCompileShader(fragment_obj);
	if (printShaderInfoLog(fragment_obj, "Fragment Source"))
		glAttachShader(program, fragment_obj);
	//削除マークを付ける
	glDeleteShader(fragment_obj);

	//Programオブジェクトのリンク
	glLinkProgram(program);

	if (printProgramInfoLog(program))
		return program;

	//Programオブジェクトの生成に失敗
	glDeleteProgram(program);

	return 0;
}

GLboolean Shader::printShaderInfoLog(GLuint ShaderObj, const GLchar * Str)
{
	//コンパイル結果を取得
	GLint status;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
		std::cout << Str << "のコンパイルに失敗しました" << std::endl;
	//コンパイル時のログの長さを取得
	GLsizei log_length;
	glGetShaderiv(ShaderObj, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 1)
	{
		//コンパイル時のログ内容の表示
		std::vector<GLchar>info_log(log_length);
		GLsizei length;
		glGetShaderInfoLog(ShaderObj, log_length, &length, &info_log[0]);
		std::cout << &info_log.front() << std::endl;
	}
	return static_cast<GLboolean>(status);
}

GLboolean Shader::printProgramInfoLog(GLuint ProgramObj)
{
	//リンク情報の取得
	GLint status;
	glGetProgramiv(ProgramObj, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
		std::cout << "Programオブジェクトのリンクに失敗しました" << std::endl;
	//リンク時のログの長さを取得
	GLsizei log_length;
	glGetProgramiv(ProgramObj, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 1)
	{
		//リンク時のログを取得
		std::vector<GLchar> info_log(log_length);
		GLsizei length;
		glGetProgramInfoLog(ProgramObj, log_length, &length, &info_log[0]);
		std::cout << &info_log.front() << std::endl;
	}
	return static_cast<GLboolean>(status);
}

GLboolean Shader::readSource(const std::string & SourceName, std::vector<GLchar>& Buffer)
{
	if (SourceName.size() == 0)
		return GL_FALSE;
	std::ifstream file(SourceName, std::ios::binary);

	if (file.fail())
	{
		std::cout << SourceName << "のファイルオープンに失敗しました" << std::endl;
		file.close();
		return GL_FALSE;
	}
	//ファイル終端に移動
	file.seekg(0L, std::ios::end);
	GLsizei length = static_cast<GLsizei>(file.tellg());
	Buffer.resize(length + 1);
	//ファイルの先頭に移動
	file.seekg(0L, std::ios::beg);
	file.clear();

	//ファイルの中を読む
	file.read(Buffer.data(), length);
	Buffer.at(length) = '\0';

	if (file.fail())
	{
		//読み込みに失敗
		std::cout << SourceName << "ファイルの読み込みに失敗しました" << std::endl;
		file.close();
		return GL_FALSE;
	}

	file.close();
	return GL_TRUE;
}
