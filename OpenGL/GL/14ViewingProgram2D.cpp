#include<GL\glut.h>
#include<iostream>

class wcPt2D {
public:
	GLfloat x, y;
};

void triangle(wcPt2D* verts){
	GLint k;
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 3; k++) {
		glVertex2f(verts[k].x, verts[k].y);
	}
	glEnd();
}

void init() {
	//设置显示窗口背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//设置世界坐标剪裁窗口的参数
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100, 100.0, -100.0, 100.0);
	//设置用于构造几何变换矩阵的模式。
	glMatrixMode(GL_MODELVIEW);
}

void displayFcn() {
	//定义三角形的初始位置
	wcPt2D verts[3] = { {-50.0,-25.0},{50.0,-25.0},{0.0,50.0} };
	//清理显示窗口
	glClear(GL_COLOR_BUFFER_BIT);
	//设置颜色填充为蓝色
	glColor3f(0.0, 0.0, 0.1);
	//设置左侧视口
	glViewport(0, 0, 300, 300);
	//绕 z 轴旋转
	glRotatef(90.0, 0.0, 0.0, 1.0);
	triangle(verts);
	glFlush();
}

int main(int argc,char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 300);
	glutCreateWindow("split-srceen example");
	init();
	glutDisplayFunc(displayFcn);
	glutMainLoop();
	return 0;
}