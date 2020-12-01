#include<GL\glut.h>
#include<iostream>
#include<cmath>
#include<stdlib.h>

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

void TrimmingFunctions() {
	GLUnurbsObj *bezSurface;

	GLfloat outerTrimPts[5][2] = { { 0.0, 0.0 },{ 1.0, 0.0 },{ 1.0, 1.0},
	{ 0.0, 1.0 },{ 0.0, 0.0 } };
	GLfloat innerTrimPts1[3][2] = { { 0.25, 0.5 },{ 0.5, 0.75 },
	{ 0.75, 0.5} };
	GLfloat innerTrimPts2[4][2] = { { 0.75, 0.5 },{ 0.75, 0.25 },
	{ 0.25, 0.25},{ 0.25, 0.5 } };

	GLfloat surfKnots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
	GLfloat trimCurveKnots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };

	bezSurface = gluNewNurbsRenderer();

	gluBeginSurface(bezSurface);
	gluNurbsSurface(bezSurface, 8, surfKnots, 8, surfKnots, 4 * 3, 3,&ctrlPts[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
	gluBeginTrim(bezSurface);
	/*  Counterclockwise outer trim curve.  */
	gluPwlCurve(bezSurface, 5, &outerTrimPts[0][0], 2, GLU_MAP1_TRIM_2);
	gluEndTrim(bezSurface);
	gluBeginTrim(bezSurface);
	/*  Clockwise inner trim-curve sections.  */
	gluPwlCurve(bezSurface, 3, &innerTrimPts1[0][0], 2, GLU_MAP1_TRIM_2);
	gluNurbsCurve(bezSurface, 8, trimCurveKnots, 2, &innerTrimPts2[0][0], 4, GLU_MAP1_TRIM_2);
	gluEndTrim(bezSurface);
	gluEndSurface(bezSurface);
}
 
void displayFcnGL() {

	glClear(GL_COLOR_BUFFER_BIT);
	TrimmingFunctions();
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