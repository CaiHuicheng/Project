#include<iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

using namespace std;

int main(int argc, char** argv[])
{
	/*glewExperimental = GL_TRUE;
	if (glewInit()!=GLEW_OK)
	{
	cout << "failed to initalize GLEW" << endl;
	return -1;
	}*/
	//初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//配置GLFW  4.X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);//配置GLFW  X.0  => 4.0
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearningOpenGL", nullptr, nullptr);
	//渲染引擎

	if (window == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();//接收事件
		glfwSwapBuffers(window);
	}


	//退出
	glfwTerminate();
	return 0;
	//glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	////glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//return 0;

}