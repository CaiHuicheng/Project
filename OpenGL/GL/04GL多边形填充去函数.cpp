#include<iostream>
#include<GL\glut.h>
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200, 0.0, 150.0);
}

void lineSegment() {
	int points[6][3] = { {25,75,0},{50,50,0},{100,50,0} ,{125,75},{100,100} ,{50,100}};
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 0.2);
	/*
		GL_LINTS		两点划线0
		GL_LINE_STRIP	生成折线
		GL_LINE_LOOP	生成封闭折线

		GL_POLYGON			单个填充多边形
		GL_TRIANGLES		填充封闭区间
		GL_TRIANGLE_STRIP	以三角形填充区间（三角坐标）
		GL_TRIANGLE_STRIP	以三角形填充区间

	*/


	glBegin(GL_TRIANGLE_FAN);
		/*glVertex2i(points[0][0],points[0][1]);
		glVertex2i(points[1][0], points[1][1]);
		glVertex2i(points[2][0], points[2][1]);*/
	
	/*
	//单个多边形 GL_POLYGON
	glVertex2iv(points[0]);
	glVertex2iv(points[1]);
	glVertex2iv(points[2]);
	glVertex2iv(points[3]);
	glVertex2iv(points[4]);
	glVertex2iv(points[5]);*/
	//生成两个不想连三角 GL_TRIANGLES
	/*
	glVertex2iv(points[0]);
	glVertex2iv(points[1]);
	glVertex2iv(points[5]);
	glVertex2iv(points[2]);
	glVertex2iv(points[3]);
	glVertex2iv(points[4]);*/

	//生成两个四个相连三角 GL_TRIANGLE_STRIP
	/*glVertex2iv(points[0]);
	glVertex2iv(points[1]);
	glVertex2iv(points[5]);
	glVertex2iv(points[2]);
	glVertex2iv(points[4]);
	glVertex2iv(points[3]);*/

	//生成两个四个相连三角 GL_TRIANGLE_STRIP
	glVertex2iv(points[0]);
	glVertex2iv(points[1]);
	glVertex2iv(points[2]);
	glVertex2iv(points[3]);
	glVertex2iv(points[4]);
	glVertex2iv(points[5]);
	
	glEnd();
	glFlush();
}

int main(int argc,char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(600, 400);
	glutCreateWindow("learning GLUT");
	
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
	
	return 0;
}