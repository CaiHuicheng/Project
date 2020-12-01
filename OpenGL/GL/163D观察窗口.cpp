#include<gl\glut.h>
#include<iostream>

GLint winWidth = 600, winHeight = 600;
//坐标原点
//GLfloat x0 = 100.0, y0 = 50.0, z0 = 50.0;
GLfloat vertex3D[3] = { 100.0, 50.0, 50.0 };
//观察点
//GLfloat xref = 50.0, yref = 50.0, zref = 0.0;
GLfloat ref[3] = { 50.0, 50.0, 0.0}; 
//矢量
//GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;
GLfloat V[3] = { 0.0, 1.0, 0.0 };
//为剪裁窗口设置坐标限制
//GLfloat xwMin = -40, ywMin = -60, xwMax = 40, ywMax = 60;
GLfloat win[2][2] = { {-40,-60},{40,60} };
//设置近剪裁平面和远剪裁平面的位置
GLfloat dnear = 25.0, dfar = 125.0;

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(vertex3D[0], vertex3D[1], vertex3D[2], ref[0], ref[1], ref[2], V[0], V[1], V[2]);
	glMatrixMode(GL_PROJECTION);
	glFrustum(win[0][0], win[1][0], win[0][1], win[1][1], dnear, dfar);
}

void displayFcn() {
	glClear(GL_COLOR_BUFFER_BIT);
	//设置方形填充区域的参数
	glColor3f(0.0, 1.0, 0.0);
	//设置线框
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	glEnd();
	glFlush();
}


void reshapeFun(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
}
int main(int argc, char**argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("3D 观察窗口");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFun);
	glutMainLoop();
}