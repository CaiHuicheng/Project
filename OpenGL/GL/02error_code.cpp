#include<iostream>
#include<GL\glut.h>

int main(int argc, char**argv) {
	GLenum code;
	const GLubyte *str;
	code = glGetError();
	str = gluErrorString(code);
	fprintf(stderr, "openGL error:%s\n", str);
	system("pause");
	return 0;
}