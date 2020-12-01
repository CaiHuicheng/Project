#include<GL\glut.h>
#include<iostream>
#include<cmath>
#include<stdlib.h>

//设置显示窗口
GLsizei winWidth = 600, winHeight = 600;

//设置世界坐标剪辑窗口的大小
GLfloat win[2][2] = { {-5,-5},{5,5} };

void init() {
	//设置显示窗口背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

//保持纵横比为1.0
void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(win[0][0], win[1][0], win[0][1], win[1][1]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLBezierCurveSurface() {
	GLfloat ctrlPts[4][4][3] = {
		{ { -1.5, -1.5,  4.0 },{ -0.5, -1.5,  2.0 },
			{ -0.5, -1.5, -1.0 },{ 1.5, -1.5,  2.0 } },
		{ { -1.5, -0.5,  1.0 },{ -0.5, -0.5,  3.0 },
			{ 0.5, -0.5,  0.0 },{ 1.5, -0.5, -1.0 } },
		{ { -1.5,  0.5,  4.0 },{ -0.5,  0.5,  0.0 },
			{ 0.5,  0.5,  3.0 },{ 1.5,  0.5,  4.0 } },
		{ { -1.5,  1.5, -2.0 },{ -0.5,  1.5, -2.0 },
			{ 0.5,  1.5,  0.0 },{ 1.5,  1.5, -1.0 } }
	};

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, &ctrlPts[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	GLint k, j;

	glColor3f(0.0, 0.0, 1.0);
	for (k = 0; k <= 8; k++)
	{
		glBegin(GL_LINE_STRIP);  // Generate Bezier surface lines.
		for (j = 0; j <= 40; j++)
			glEvalCoord2f(GLfloat(j) / 40.0, GLfloat(k) / 8.0);
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (j = 0; j <= 40; j++)
			glEvalCoord2f(GLfloat(k) / 8.0, GLfloat(j) / 40.0);
		glEnd();
	}
}
 
void displayFcnGL() {

	glClear(GL_COLOR_BUFFER_BIT);
	GLBezierCurveSurface();
	glFlush();
}

void main(int argc, char**argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Bezier Curve");
	init();
	glutDisplayFunc(displayFcnGL);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}