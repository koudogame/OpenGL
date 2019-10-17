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

	//OpenGLの描画対象に設定
	glfwMakeContextCurrent(window_);

	//GLEWの初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		//エラー
		std::cout << "GLEWの初期化に失敗" << std::endl;
		return false;
	}
	//垂直同期のタイミングを待つ
	glfwSwapInterval(1);

	//クリアカラーの選択
	glClearColor(1.0F, 1.0F, 1.0F, 1.0F);

	//背面カリングを有効にする
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//Zバッファを有効にする
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
	//画面クリア
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Window::swapWindow()
{
	//画面更新
	glfwSwapBuffers(window_);

	//イベントの取り出し
	//glfwWaitEvents();
	glfwPollEvents();
}
