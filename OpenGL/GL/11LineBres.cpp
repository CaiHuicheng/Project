#include<GL\glut.h>
#include<math.h>
#include<iostream>
#include<stdlib.h>

GLsizei winWidth = 400, winHeight = 300;

static void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200, 0.0, 150);
}

void setPixel(GLint xCoord, GLint yCoord) {
	glBegin(GL_POINTS);
	glVertex2i(xCoord, yCoord);
	glEnd();
}

inline int roundFloat(const float a) {
	return int(a + 0.5);
}


void lineDDA(int x0, int y0, int xEnd, int yEnd) {
	int dx = xEnd - x0, dy = yEnd - y0, steps, k;
	float xI, yI, x = x0, y = y0;
	if (fabs(dx) > fabs(dy)) {
		steps = fabs(dx);
	}
	else {
		steps = fabs(dy);
	}
	xI = float(dx) / float(steps);
	yI = float(dy) / float(steps);
	setPixel(roundFloat(x), roundFloat(y));
	for (k = 0; k < steps; k++) {
		x += xI;
		y += yI;
		setPixel(roundFloat(x), roundFloat(y));
	}
}

void lineBres(int x0, int y0, int xEnd, int yEnd) {
	int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int x, y;
	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = 0;
	}
	else {
		x = x0; y = y0;
	}
	setPixel(x, y);
	while (x < xEnd) {
		x++;
		if (p < 0) {
			p += twoDy;
		}
		else {
			y++;
			p += twoDyMinusDx;
		}
		setPixel(x, y);
	}
}

void winReshapeFcn(int newWidth,int newHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.1);
	/*lineDDA(50,50,200,200);*/
	lineBres(50, 50, 200, 200);
	glFlush();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Pie Chart Data Port");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}