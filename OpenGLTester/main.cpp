#include "Window.h"
#include "Model.h"
#include "Camera.h"

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


	glm::vec3 eye = { 2.0F,2.0F,10.0F };
	glm::vec3 target = { 0.0F,0.0F,0.0F };
	glm::vec3 up = { 0.0F,1.0F,0.0F };
	Camera::Get()->setView(eye, target, up);
	Camera::Get()->setProjection(glm::radians(30.0F), 1280.0F / 720.0F, 0.1F, 100.0F);

	while (window.isCloseWindow())
	{
		window.clearWindow();
		model.updata();
		model.draw();

		window.swapWindow();
	}
	return 0;
};