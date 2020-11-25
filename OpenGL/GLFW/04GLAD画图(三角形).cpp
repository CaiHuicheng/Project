#include<glad\glad.h>
#include<iostream>
#include<GLFW\glfw3.h>
using namespace std;



//����������
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
	//��Ⱦ
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0.3,GL_STATIC_DRAW);//������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//�˳�
	glfwTerminate();
	return 0;
}

void VAOSet() {
	//����VBO ���㻺�����;VAO����VBO
	unsigned int VBO,VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	//���Կ�дֵ
	/*
		GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
		GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
		GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//��ɫ������ 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void init() {
	//��ʼ��
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
	//����������
	glfwMakeContextCurrent(window);

	//glad��ʼ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "error : gladLoadGLLoader is nullptr" << endl;
		return ;
	}
}