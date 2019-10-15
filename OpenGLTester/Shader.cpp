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
	//Shader�\�[�X�̓ǂݍ���
	std::vector<GLchar> vertex_buffer;
	GLboolean vertex_tester = readSource(VertexShaderSourceName, vertex_buffer);
	std::vector<GLchar> fragment_buffer;
	GLboolean fragment_tester = readSource(FragmentShaderSourceName, fragment_buffer);

	return vertex_tester && fragment_tester ? createProgram(vertex_buffer.data(), fragment_buffer.data()) : 0;
}

GLuint Shader::createProgram(const GLchar * VertexSource, const GLchar * FragmentSource)
{
	//Program�I�u�W�F�N�g�̍쐬
	const GLuint program(glCreateProgram());
	//Vertex Shader �I�u�W�F�N�g�̍쐬
	const GLuint vertex_obj(glCreateShader(GL_VERTEX_SHADER));
	//Source�̎���
	glShaderSource(vertex_obj, 1, &VertexSource, nullptr);
	//Shader�̃R���p�C��
	glCompileShader(vertex_obj);
	if (printShaderInfoLog(vertex_obj, "Vertex Source"))
		glAttachShader(program, vertex_obj);
	//�폜�}�[�N��t����
	glDeleteShader(vertex_obj);

	//Fragment Shader�I�u�W�F�N�g�̍쐬
	const GLuint fragment_obj(glCreateShader(GL_FRAGMENT_SHADER));
	//Source�̎���
	glShaderSource(fragment_obj, 1, &FragmentSource, nullptr);
	//�R���p�C��
	glCompileShader(fragment_obj);
	if (printShaderInfoLog(fragment_obj, "Fragment Source"))
		glAttachShader(program, fragment_obj);
	//�폜�}�[�N��t����
	glDeleteShader(fragment_obj);

	//Program�I�u�W�F�N�g�̃����N
	glLinkProgram(program);

	if (printProgramInfoLog(program))
		return program;

	//Program�I�u�W�F�N�g�̐����Ɏ��s
	glDeleteProgram(program);

	return 0;
}

GLboolean Shader::printShaderInfoLog(GLuint ShaderObj, const GLchar * Str)
{
	//�R���p�C�����ʂ��擾
	GLint status;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
		std::cout << Str << "�̃R���p�C���Ɏ��s���܂���" << std::endl;
	//�R���p�C�����̃��O�̒������擾
	GLsizei log_length;
	glGetShaderiv(ShaderObj, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 1)
	{
		//�R���p�C�����̃��O���e�̕\��
		std::vector<GLchar>info_log(log_length);
		GLsizei length;
		glGetShaderInfoLog(ShaderObj, log_length, &length, &info_log[0]);
		std::cout << &info_log.front() << std::endl;
	}
	return static_cast<GLboolean>(status);
}

GLboolean Shader::printProgramInfoLog(GLuint ProgramObj)
{
	//�����N���̎擾
	GLint status;
	glGetProgramiv(ProgramObj, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
		std::cout << "Program�I�u�W�F�N�g�̃����N�Ɏ��s���܂���" << std::endl;
	//�����N���̃��O�̒������擾
	GLsizei log_length;
	glGetProgramiv(ProgramObj, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 1)
	{
		//�����N���̃��O���擾
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
		std::cout << SourceName << "�̃t�@�C���I�[�v���Ɏ��s���܂���" << std::endl;
		file.close();
		return GL_FALSE;
	}
	//�t�@�C���I�[�Ɉړ�
	file.seekg(0L, std::ios::end);
	GLsizei length = static_cast<GLsizei>(file.tellg());
	Buffer.resize(length + 1);
	//�t�@�C���̐擪�Ɉړ�
	file.seekg(0L, std::ios::beg);
	file.clear();

	//�t�@�C���̒���ǂ�
	file.read(Buffer.data(), length);
	Buffer.at(length) = '\0';

	if (file.fail())
	{
		//�ǂݍ��݂Ɏ��s
		std::cout << SourceName << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << std::endl;
		file.close();
		return GL_FALSE;
	}

	file.close();
	return GL_TRUE;
}
