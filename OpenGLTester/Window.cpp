#include "stdafx.h"
#include "Window.h"


Window::Window(GLuint Width, GLuint Height,const GLchar * Name) :
	window_(glfwCreateWindow(Width, Height, Name, nullptr, nullptr))
{
}

Window::~Window()
{
}

bool Window::init()
{
	if (window_ == nullptr)
		return false;

	//OpenGL�̕`��Ώۂɐݒ�
	glfwMakeContextCurrent(window_);

	//GLEW�̏�����
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		//�G���[
		std::cout << "GLEW�̏������Ɏ��s" << std::endl;
		return false;
	}
	//���������̃^�C�~���O��҂�
	glfwSwapInterval(1);

	//�N���A�J���[�̑I��
	glClearColor(1.0F, 1.0F, 1.0F, 1.0F);

	//�w�ʃJ�����O��L���ɂ���
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//Z�o�b�t�@��L���ɂ���
	glEnable(GL_DEPTH_TEST);

	return true;
}

bool Window::isCloseWindow()
{
	return glfwWindowShouldClose(window_) == GL_FALSE &&
		glfwGetKey(window_, GLFW_KEY_ESCAPE) == GL_FALSE;
}

void Window::clearWindow()
{
	//��ʃN���A
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Window::swapWindow()
{
	//��ʍX�V
	glfwSwapBuffers(window_);

	//�C�x���g�̎��o��
	//glfwWaitEvents();
	glfwPollEvents();
}
