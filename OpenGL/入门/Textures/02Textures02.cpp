#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ���嶥����ɫ��
// ������Ҫ����������ɫ��ʹ���ܹ����ܶ�������Ϊһ���������ԣ��������괫��Ƭ����ɫ��
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	ourColor = aColor;\n"
"	TexCoord = aTexCoord;\n"
"}\0";

// ����Ƭ����ɫ��
// texture��GLSL�ڽ��Ĳ���������ɫ�ĺ���
// ����һ��������������������ڶ��������Ƕ�Ӧ���������ꡣ
// texture������ʹ��֮ǰ���õ������������Ӧ����ɫֵ���в���
// ���������ɫ��������������Ľ�ϡ�
// GLSL�ڽ���mix������Ҫ��������ֵ��Ϊ�������������Ǹ��ݵ����������������Բ�ֵ��
// ���������ֵ��0.0�����᷵�ص�һ�����룻�����1.0���᷵�صڶ�������ֵ��
// 0.2�᷵��80%�ĵ�һ��������ɫ��20%�ĵڶ���������ɫ����������������Ļ��ɫ��
const char *fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"void main()\n"
"{\n"
"	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// ÿ�δ��ڱ仯ʱ��������ͼ�εĻ��ƴ��ڣ��������Ϊ����
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char **argv)
{
	// ��ʼ�������ð汾�ţ����ú���ģʽ
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��������
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "mytest", NULL, NULL);
	if (!window)
	{
		std::cout << "Create Window Error!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// ע�ᴰ�ڴ�С�仯�Ļص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ��ʼ��glad
	// ���Ǹ�GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ�����
	// GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ�����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		glfwDestroyWindow(window);
		return -1;
	}

	unsigned int vertexShader;
	// ����һ��������ɫ��
	// ����ɫ������Դ��
	// ������ɫ��
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512] = { 0 };
	// ��ȡ��ɫ������״̬
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// ���������󣬻�ȡ������Ϣ
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ����Ƭ����ɫ��������������Ķ�����ɫ��
	int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		memset(infoLog, 0, sizeof(infoLog));
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* ��������ɫ����Ҫ�������ɫ������Ϊһ����ɫ��������� */
	// ����һ����ɫ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// �����ɫ������ɫ���������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// ��������
	glLinkProgram(shaderProgram);

	// �������ɫ��һ������Ҫ��������Ƿ�ɹ�
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		memset(infoLog, 0, sizeof(infoLog));
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// ���ӳɹ���Ϳ��Լ�����ɫ������
	glUseProgram(shaderProgram);

	// ���ˣ������Ѿ�����Ҫ֮ǰ������Ƭ����ɫ���ˣ���ɾ�˰�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ����ͼƬ����
	// ����ͼƬ�����Լ�д��Ҳ����ʹ�ÿ⣬ʲô��ʽ����Ҫ��ֻҪ�ܰ�ͼƬ��ȡ���ڴ����
	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "Failed to load texture" << std::endl;
		// ������ʾ�����룬������Ͳ����ˣ�ֱ���˳�
		return 0;
	}

	// ����һ�������ڴ����
	unsigned int texture1;
	glGenTextures(1, &texture1);

	// ���������
	glBindTexture(GL_TEXTURE_2D, texture1);

	// ���û���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// ���ù���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// ͼƬ��������֮����ò����ˣ�����ɾ����
	stbi_image_free(data);

	// ��ΪOpenGLҪ��y��0.0��������ͼƬ�ĵײ��ģ�����ͼƬ��y��0.0����ͨ���ڶ�����
	// Ϊ��ֹͼ��ߵ�����ͼ�����ʱ��תy��
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "Failed to load texture" << std::endl;
		// ������ʾ�����룬������Ͳ����ˣ�ֱ���˳�
		return 0;
	}

	// ����һ�������ڴ����
	unsigned int texture2;
	glGenTextures(1, &texture2);

	// ���������
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// ͼƬ��������֮����ò����ˣ�����ɾ����
	stbi_image_free(data);

	// ʹ������
	// ���ȶ��������������Ķ�������
	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};

	// �����������飬����ÿ�������ζ�����������
	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	// ����һ���ڴ滺�����
	glGenBuffers(1, &VBO);
	// ����һ�������������
	glGenBuffers(1, &EBO);
	// ����һ�������������
	glGenVertexArrays(1, &VAO);

	// ���Ȱ󶨶���������󣬣���
	glBindVertexArray(VAO);

	// Ȼ���ڴ�����Ϊ���㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// �򻺳��ڴ�д������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// �����У����ǻ�ҪΪ�������������ڴ����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// �������������д������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// ��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ��ע�⣬��������ģ�
	// ��glVertexAttribPointer�ĵ��ý�VBOע��Ϊ�������Եİ󶨶��㻺��������
	// ������ǿ��԰�ȫ�ؽ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ��������֮��ȡ����VAO���Ա�����VAO���ò���������޸Ĵ�VAO��������������ٷ�����
	// �޸�����VAO��Ҫ����glBindVertexArray���������ͨ�������ڲ�ֱ����Ҫʱȡ����VAO��Ҳ����VBO����
	glBindVertexArray(0);


	// ������ɫ������
	glUseProgram(shaderProgram);
	// ����ÿ���������ķ�ʽ����OpenGLÿ����ɫ�������������ĸ�����Ԫ
	// ����ֻ��Ҫ����һ�μ��ɣ���������������Ⱦѭ����ǰ��
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

	// ������Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ���������¼�
		processInput(window);

		// ��ձ�����ɫ
		// ������glClear�����������ɫ����֮��
		// ������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ
		// ��������ǽ���Ļ����Ϊ�����ƺڰ��������ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*****************************************************************
		OpenGL���ٱ�֤��16������Ԫ����ʹ�ã�Ҳ����˵����Լ����GL_TEXTURE0��GL_TEXTRUE15��
		���Ƕ��ǰ�˳����ģ���������Ҳ����ͨ��GL_TEXTURE0 + 8�ķ�ʽ���GL_TEXTURE8��
		���ڵ�������Ҫѭ��һЩ����Ԫ��ʱ�������á�
		*******************************************************************/
		// �ڰ�����֮ǰ�ȼ�������Ԫ
		glActiveTexture(GL_TEXTURE0);
		// �������Զ�������ֵ��Ƭ����ɫ���Ĳ�����
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
		Sleep(1);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	glfwDestroyWindow(window);

	return 0;
}