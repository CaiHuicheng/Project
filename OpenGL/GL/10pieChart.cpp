#include<GL\glut.h>
#include<math.h>
#include<iostream>
#include<stdlib.h>

const double twoPi = 6.2831583;

class strPt {
public:
	GLint x, y;
};

class screenPt {
public:
	screenPt() {
		x = y = 0;
	}
	GLint x, y;

	void setCoords(GLint xCoordValue, GLint yCorrdValue) {
		x = xCoordValue;
		y = yCorrdValue;
	}
	GLint getx() const {
		return x;
	}
	GLint gety() const {
		return y;
	}
	void incrementx() {
		x++;
	}
	void incrementy() {
		y--;
	}
};


GLsizei winWidth = 400, winHeight = 300;


static void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200, 0.0, 150);
}


void circleMidpoint(GLint xc, GLint yc, GLint radius) {
	screenPt circPt;
	GLint p = 1 - radius;//中点參数初值
	circPt.setCoords(0, radius);//Set coords for top point of circle
	void circlePlotPoints(GLint, GLint, screenPt);
	/*Plot the initial point in each circle quadrant*/
	circlePlotPoints(xc, yc, circPt);
	/*Calculate next point and plot in each octant*/
	while (circPt.getx() < circPt.gety()) {
		circPt.incrementx();
		if (p < 0)
			p += 2 * circPt.getx() + 1;
		else {
			circPt.incrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}

void setPixel(GLint xCoord, GLint yCoord) {
	glBegin(GL_POINTS);
	glVertex2i(xCoord, yCoord);
	glEnd();
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt)
{
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}

void Bresenham_Circle(int xc, int yc, int r)
{
	int x, y, d;
	x = 0;
	y = r;
	d = 3 - 2 * r;
	glVertex2i(x + xc, y + yc);
	while (x < y)
	{
		if (d < 0)
		{
			d = d + 4 * x + 6;
		}
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
		glVertex2i(x + xc, y + yc);
		glVertex2i(y + xc, x + yc);
		glVertex2i(y + xc, -x + yc);
		glVertex2i(x + xc, -y + yc);
		glVertex2i(-x + xc, -y + yc);
		glVertex2i(-y + xc, -x + yc);
		glVertex2i(-x + xc, y + yc);
		glVertex2i(-y + xc, x + yc);
	}
}


void pieChart() {
	strPt circCtr, piePt;
	GLint radius = winWidth / 4;
	GLdouble sliceAngle, previousSliceAngle = 0.0;
	GLint k, nSlices = 12;
	GLfloat dataValue[12] = { 10.0,7.0,13.0,5.0,13.0,14.0,3.0,16.0,5.0,3.0,17.0,8.0 };
	GLfloat dataSum = 0.0;
	circCtr.x = winWidth / 2;
	circCtr.y = winHeight / 2;
	circleMidpoint(circCtr.x, circCtr.y, radius);
	//Bresenham_Circle(circCtr.x, circCtr.y, radius);

	for (k = 0; k < nSlices; k++) {
		dataSum += dataValue[k];
	}
	for (k = 0; k < nSlices; k++) {
		sliceAngle = twoPi*dataValue[k] / dataSum + previousSliceAngle;
		piePt.x = circCtr.x + radius*cos(sliceAngle);
		piePt.y = circCtr.y + radius*sin(sliceAngle);
		glBegin(GL_LINE);
			glVertex2i(circCtr.x, circCtr.y);
			glVertex2i(piePt.x, piePt.y);
		glEnd();
		previousSliceAngle = sliceAngle;
	}
}


void winReshapeFcn(int newWidth,int newHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	winWidth = newWidth;
	winHeight = newHeight;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.1);
	pieChart();
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