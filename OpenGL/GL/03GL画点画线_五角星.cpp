#include<iostream>
#include<GL\glut.h>
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200, 0.0, 150.0);
}

void lineSegment() {
	int points[5][3] = { {50,50,0},{100,150,0},{150,50,0} ,{50,125},{150,125} };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 0.2);
	/*
		GL_LINTS		两点划线0
		GL_LINE_STRIP	生成折线
		GL_LINE_LOOP	生成封闭折线
	*/
	glBegin(GL_LINE_LOOP);
		/*glVertex2i(points[0][0],points[0][1]);
		glVertex2i(points[1][0], points[1][1]);
		glVertex2i(points[2][0], points[2][1]);*/
	glVertex2iv(points[0]);
	glVertex2iv(points[1]);
	glVertex2iv(points[2]);
	glVertex2iv(points[3]);
	glVertex2iv(points[4]);
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