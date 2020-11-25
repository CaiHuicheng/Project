#include<glad\glad.h>
#include<iostream>
#include<GLFW\glfw3.h>
using namespace std;



//三角形坐标
float vertices[] = {//z = 0
	0.0f, 0.5f, 0.0f,	//(x1,y2)
	0.5f, -0.5f,0.0f,	//(x2,y2)
	-0.5f, -0.5f,0.0f	//(x3,y3)
};

void init();
void VAOSet();

GLFWwindow *window;

int main() {

	init();
	VAOSet();
	//渲染
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0.3,GL_STATIC_DRAW);//画三角
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//退出
	glfwTerminate();
	return 0;
}

void VAOSet() {
	//生成VBO 顶点缓冲对象;VAO管理VBO
	unsigned int VBO,VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//绑定
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	//往显卡写值
	/*
		GL_STATIC_DRAW ：数据不会或几乎不会改变。
		GL_DYNAMIC_DRAW：数据会被改变很多。
		GL_STREAM_DRAW ：数据每次绘制时都会改变。
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//着色器解释 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void init() {
	//初始化
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Set GLAD", nullptr, nullptr);


	if (window == nullptr) {
		cout << "error : window is nullptr" << endl;
		glfwTerminate();
		return ;
	}
	//设置上下文
	glfwMakeContextCurrent(window);

	//glad初始化
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "error : gladLoadGLLoader is nullptr" << endl;
		return ;
	}
}