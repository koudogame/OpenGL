#include "Window.h"
#include "Model.h"

int main()
{
	//GLFWの初期化
	if (glfwInit() == GL_FALSE)
	{
		//エラー
		std::cout << "GLFWの初期化に失敗" << std::endl;
		return 1;
	}
	atexit(glfwTerminate);

	//プロファイルの選択
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window window;
	if (!window.init())
		return 0;

	Model model;
	if (!model.init())
		return 0;

	while (window.isCloseWindow())
	{
		window.clearWindow();

		model.draw();

		window.swapWindow();
	}
	return 0;
};