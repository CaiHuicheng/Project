#include<GL\glut.h>
#include<iostream>
#include<cmath>
#include<stdlib.h>

//设置显示窗口
GLsizei winWidth = 600, winHeight = 600;

//设置世界坐标剪辑窗口的大小
GLfloat win[2][2] = { {-50,-50},{50,50} };

class Point {
public:
	GLfloat x, y, z;
};

void init() {
	//设置显示窗口背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

//画点
void plotPoint(Point bezCurvePt) {
	glBegin(GL_POINTS);
	glVertex2f(bezCurvePt.x, bezCurvePt.y);
	glEnd();
}

void binomialCoeffs(GLint n, GLint * c) {
	GLint k, j;
	for (k = 0; k <= n; k++) {
		/*	n!/(k!(n - k)!)	*/
		c[k] = 1;
		for (j = n; j >= k + 1; j--) {
			c[k] *= j;
		}
		for (j = n - k; j >= 2; j--) {
			c[k] /= j;
		}
	}
}

void computeBezPt(GLfloat u, Point *bezP, GLint nCtrlPts, Point *ctrlP, GLint *c) {
	GLint k, n = nCtrlPts - 1;
	GLfloat bezBlendFcn;
	bezP->x = bezP->y = bezP->z = 0.0;

	for (k = 0; k < nCtrlPts; k++) {
		bezBlendFcn = c[k] * pow(u, k) * pow(1 - u, n - k);
		bezP->x += ctrlP[k].x*bezBlendFcn;
		bezP->y += ctrlP[k].y*bezBlendFcn;
		bezP->z += ctrlP[k].z*bezBlendFcn;
	}
}

//Bezier curve
void bezier(Point* ctrlP, GLint nCtrlPs, GLint nBezCurvePs) {
	Point bezCurveP;
	GLfloat u;
	GLint *c, k;
	c = new GLint[nCtrlPs];
	binomialCoeffs(nCtrlPs - 1, c);
	for (k = 0; k <= nBezCurvePs; k++) {
		u = GLfloat(k) / GLfloat(nBezCurvePs);
		computeBezPt(u, &bezCurveP, nCtrlPs, ctrlP, c);
		plotPoint(bezCurveP);
	}
	delete[] c;
}
//设定Bezier curve绘制的控制点数量和曲线位置数。
void displayFcn() {
	GLint nCtrlPs = 4, nBezCurvePs = 1000;
	Point ctrlPs[4] = { {-40.0, -40.0, 0.0},{-10.0, 200.0, 0.0},{10.0, -200.0, 0.0},{40.0, 40.0, 0.0} };
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4);
	glColor3f(1.0, 0.0, 0.0);
	bezier(ctrlPs, nCtrlPs, nBezCurvePs);
	glFlush();
}

//保持纵横比为1.0
void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(win[0][0], win[1][0], win[0][1], win[1][1]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void main(int argc, char**argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Bezier Curve");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}