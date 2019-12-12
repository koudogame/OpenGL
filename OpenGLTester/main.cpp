#include "Window.h"
#include "Model.h"
#include "CameraManager.h"
#include "Loop.h"

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

	Loop loop;
	if (!loop.init())
		return 0;

	while (window.isCloseWindow())
	{
		window.clearWindow();
		if (!loop.update())
			break;

		loop.draw();

		window.swapWindow();
	}
	loop.destroy();
	return 0;
};