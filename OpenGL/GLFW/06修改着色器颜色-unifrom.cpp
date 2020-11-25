#include<glad\glad.h>
#include<iostream>
#include<GLFW\glfw3.h>
using namespace std;


//三角形坐标
float vertices[] = {//z = 0
	-0.5f, -0.5f, 0.0f,	//(x1,y2)
	0.5f, -0.5f,0.0f,	//(x2,y2)
	0.5f, 0.5f, 0.0f,	//(x3,y3)
	- 0.5f, 0.5f,0.0f	//(x4,y4)
};
//vertex 三角形索引
unsigned int indices[] = {
	0,1,3,
	1,2,3
};

void init();
void EBOSet();
void shadersSet();


GLFWwindow *window;
int shaderProgram;

int main() {

	init();
	EBOSet();
	shadersSet();
	//设置边框模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE/*GL_FILL*/);
	//渲染
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glDrawArrays(GL_TRIANGLES, 0.6, GL_STATIC_DRAW);//画三角

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//退出
	glfwTerminate();
	return 0;
}

void shadersSet() {
	//编译片段着色器 生成橙色三角
	/*
	源码：
	#version 330 core
	out vec4 FragColor;

	void main()
	{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}

	1、着色器源码存入字符串
	2、创建着色器对象
	3、源码字符串赋予着色器对象
	4、编译着色器

	1、创建着色器对象
	2、编译好的着色器附加到程序对象上
	3、链接生成程序

	*/
	const char * fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 outColor;\n"
		"void main() {\n"
		"	FragColor = outColor;\n"
		"}\n\0";

	const char * vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\n\0";


	//编译着色器
	//2、创建着色器对象
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//3、源码字符串赋予着色器对象	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//4、编译着色器
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//1、创建着色器对象
	shaderProgram = glCreateProgram();
	//2、编译好的着色器附加到程序对象上
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//3、链接生成程序
	glLinkProgram(shaderProgram);

	//获取uniform位置
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");
	glUseProgram(shaderProgram);//使用顶点、片段着色器
	glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);

}

void EBOSet() {
	//生成VBO 顶点缓冲对象;VAO管理VBO
	unsigned int VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//绑定
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//往显卡写值
	/*
	GL_STATIC_DRAW ：数据不会或几乎不会改变。
	GL_DYNAMIC_DRAW：数据会被改变很多。
	GL_STREAM_DRAW ：数据每次绘制时都会改变。
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
		return;
	}
	//设置上下文
	glfwMakeContextCurrent(window);

	//glad初始化
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "error : gladLoadGLLoader is nullptr" << endl;
		return;
	}
}