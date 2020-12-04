#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 定义顶点着色器
// 我们需要调整顶点着色器使其能够接受顶点坐标为一个顶点属性，并把坐标传给片段着色器
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

// 定义片段着色器
// texture是GLSL内建的采样纹理颜色的函数
// 它第一个参数是纹理采样器，第二个参数是对应的纹理坐标。
// texture函数会使用之前设置的纹理参数对相应的颜色值进行采样
// 最终输出颜色现在是两个纹理的结合。
// GLSL内建的mix函数需要接受两个值作为参数，并对它们根据第三个参数进行线性插值。
// 如果第三个值是0.0，它会返回第一个输入；如果是1.0，会返回第二个输入值。
// 0.2会返回80%的第一个输入颜色和20%的第二个输入颜色，即返回两个纹理的混合色。
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
	// 每次窗口变化时重新设置图形的绘制窗口，可以理解为画布
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char **argv)
{
	// 初始化，配置版本号，配置核心模式
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "mytest", NULL, NULL);
	if (!window)
	{
		std::cout << "Create Window Error!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// 注册窗口大小变化的回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 初始化glad
	// 我们给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。
	// GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		glfwDestroyWindow(window);
		return -1;
	}

	unsigned int vertexShader;
	// 创建一个顶点着色器
	// 给着色器附加源码
	// 编译着色器
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512] = { 0 };
	// 获取着色器编译状态
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// 如果编译错误，获取错误信息
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 编译片段着色器，过程如上面的顶点着色器
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

	/* 创建好着色器后，要将多个着色器链接为一个着色器程序对象 */
	// 创建一个着色器程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// 添加着色器到着色器程序对象
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// 链接它们
	glLinkProgram(shaderProgram);

	// 与编译着色器一样，需要检测链接是否成功
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		memset(infoLog, 0, sizeof(infoLog));
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// 链接成功后就可以激活着色器程序
	glUseProgram(shaderProgram);

	// 至此，我们已经不需要之前的两个片段着色器了，就删了吧
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 加载图片纹理
	// 加载图片可以自己写，也可以使用库，什么方式不重要，只要能把图片读取到内存就行
	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "Failed to load texture" << std::endl;
		// 由于是示例代码，错误处理就不做了，直接退出
		return 0;
	}

	// 创建一个纹理内存对象
	unsigned int texture1;
	glGenTextures(1, &texture1);

	// 绑定纹理对象
	glBindTexture(GL_TEXTURE_2D, texture1);

	// 设置环绕
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// 设置过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// 图片生成纹理之后就用不掉了，可以删掉了
	stbi_image_free(data);

	// 因为OpenGL要求y轴0.0坐标是在图片的底部的，但是图片的y轴0.0坐标通常在顶部。
	// 为防止图像颠倒，在图像加载时翻转y轴
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "Failed to load texture" << std::endl;
		// 由于是示例代码，错误处理就不做了，直接退出
		return 0;
	}

	// 创建一个纹理内存对象
	unsigned int texture2;
	glGenTextures(1, &texture2);

	// 绑定纹理对象
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// 图片生成纹理之后就用不掉了，可以删掉了
	stbi_image_free(data);

	// 使用纹理
	// 首先定义包含纹理坐标的顶点数组
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	// 定义索引数组，就是每个三角形都用哪三个点
	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	// 创建一个内存缓冲对象
	glGenBuffers(1, &VBO);
	// 创建一个索引缓冲对象
	glGenBuffers(1, &EBO);
	// 创建一个顶点数组对象
	glGenVertexArrays(1, &VAO);

	// 首先绑定顶点数组对象，，。
	glBindVertexArray(VAO);

	// 然后将内存对象绑定为顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 向缓冲内存写入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 本例中，我们还要为索引缓冲对象绑定内存对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 向索引缓冲对象写入数据
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 纹理属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 请注意，这是允许的，
	// 对glVertexAttribPointer的调用将VBO注册为顶点属性的绑定顶点缓冲区对象，
	// 因此我们可以安全地解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 您可以在之后取消绑定VAO，以便其他VAO调用不会意外地修改此VAO，但这种情况很少发生。
	// 修改其他VAO需要调用glBindVertexArray，因此我们通常不会在不直接需要时取消绑定VAO（也不是VBO）。
	glBindVertexArray(0);


	// 激活着色器程序
	glUseProgram(shaderProgram);
	// 设置每个采样器的方式告诉OpenGL每个着色器采样器属于哪个纹理单元
	// 我们只需要设置一次即可，所以这个会放在渲染循环的前面
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

	// 创建渲染循环
	while (!glfwWindowShouldClose(window))
	{
		// 处理输入事件
		processInput(window);

		// 清空背景颜色
		// 当调用glClear函数，清除颜色缓冲之后，
		// 整个颜色缓冲都会被填充为glClearColor里所设置的颜色
		// 在这里，我们将屏幕设置为了类似黑板的深蓝绿色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*****************************************************************
		OpenGL至少保证有16个纹理单元供你使用，也就是说你可以激活从GL_TEXTURE0到GL_TEXTRUE15。
		它们都是按顺序定义的，所以我们也可以通过GL_TEXTURE0 + 8的方式获得GL_TEXTURE8，
		这在当我们需要循环一些纹理单元的时候会很有用。
		*******************************************************************/
		// 在绑定纹理之前先激活纹理单元
		glActiveTexture(GL_TEXTURE0);
		// 绑定纹理，自动把纹理赋值给片段着色器的采样器
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