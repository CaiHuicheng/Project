#include"glad\glad.h"
#include<iostream>
#include<GLFW\glfw3.h>
using namespace std;

int main() {
	//初始化
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Set GLAD", nullptr, nullptr);

	if (window == nullptr) {
		cout << "error : window is nullptr" << endl;
		glfwTerminate();
		return -1;
	}
	//设置上下文
	glfwMakeContextCurrent(window);

	//glad初始化
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "error : gladLoadGLLoader is nullptr" << endl;
		return -1;
	}

	//渲染
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//退出
	glfwTerminate();
	return 0;
}