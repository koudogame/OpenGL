#include "Window.h"
#include "Model.h"
#include "CameraManager.h"
#include "Loop.h"

int main()
{
	//GLFW�̏�����
	if (glfwInit() == GL_FALSE)
	{
		//�G���[
		std::cout << "GLFW�̏������Ɏ��s" << std::endl;
		return 1;
	}
	atexit(glfwTerminate);

	//�v���t�@�C���̑I��
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