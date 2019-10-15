#pragma once
class Window
{
public:
	Window(GLuint Width = 1280, GLuint Height = 720,const GLchar* Name = "Title");
	~Window();

public:
	bool init();
	bool isCloseWindow();
	void clearWindow();
	void swapWindow();

private:
	GLFWwindow* const window_;
};

