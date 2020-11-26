#include<iostream>
#include<GL\glut.h>
typedef GLint vertex3[3];
vertex3 points[8] = { { 0,0,0 },{ 0,1,0 },{ 1,0,0 },{ 1,1,0 },
{ 0,0,1 } ,{ 0,1,1 },{ 1,0,1 },{ 1,1,1 } };

void cube();

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200, 0.0, 150.0);
}

void lineSegment() {
	/*int points[8][3] = { {0,0,0}, {0,1,0},{1,0,0},{1,1,0},
						 {0,0,1} ,{0,1,1},{1,0,1},{1,1,1} };*/
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 0.2);
	//cube();
	glBegin(GL_QUADS);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_INT, 0, points);
		GLubyte vertexIndex[] = { 6,2,3,7,5,1,0,4,7,3,1,5,4,0,2,6,2,0,1,3,7,5,4,6 };
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, vertexIndex);
	glEnd();
	glFlush();
}

void quad(GLint n1, GLint n2, GLint n3, GLint n4) {
	glBegin(GL_QUADS);
		glVertex3iv(points[n1]);
		glVertex3iv(points[n2]);
		glVertex3iv(points[n3]);
		glVertex3iv(points[n4]);
	glEnd();
}

void cube() {
	quad(6, 2, 3, 7);
	quad(5, 1, 0, 4);
	quad(7, 3, 1, 5);
	quad(4, 0, 2, 6);
	quad(2, 0, 1, 3);
	quad(7, 5, 4, 6);
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