#include<iostream>
#include<GL\glut.h>


GLenum checkError() {
	GLenum code;
	const GLubyte *str;
	code = glGetError();
	if (code != GL_NO_ERROR) {
		str = gluErrorString(code);
		fprintf(stderr, "openGL error:%s\n", str);
	}
	return code;
}

int main(int argc, char**argv) {
	GLenum code = checkError();
	std::cout << "GLenum code:" << code << std::endl;
	system("pause");
	return 0;
}