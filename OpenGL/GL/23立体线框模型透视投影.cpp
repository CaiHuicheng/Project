#include <iostream>
#include <GL/glut.h>

/* -- - 常量-- - */
const int HEIGHT(800);
const int WIDTH(800);

void Display();
void Reshape(int w, int h);

int time(0);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//glut初始化

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//双缓存模式

	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(50, 100);
	//窗口初始化

	glClearColor(0, 0, 0, 1);
	//窗口颜色

	glutCreateWindow("Window - 3D");
	//窗口

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	return 0;
}

void Display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(4, 0, 1.5, 0, 0, 0, 1, 1, time++);

	time >= 3 ? time = -3 : time;

	std::cout << "当前观察角度：(" << 1 << ", " << 1 << ", " << time << ")" << std::endl;

	//绘制正方体的面
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	//---1---
	glNormal3f(-1, 0, 0);//设置点的法向量
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	//---2---
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	//---3---
	glNormal3f(0, 1, 0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	//---4---
	glNormal3f(0, -1, 0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	//---5---
	glNormal3f(0, 0, 1);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	//---6---
	glNormal3f(0, 0, -1);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	//draw
	glColor3f(0, 0, 0);
	glLineWidth(2.0f);
	//绘制正方体的边
	glBegin(GL_LINES);
	//---1---
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	//---2---
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	//---3---
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	//---4---
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	//双缓存使用glutSwapBuffers，但缓存glFlush
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}
