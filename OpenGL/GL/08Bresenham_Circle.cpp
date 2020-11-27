#include<windows.h>
#include<GL/glut.h>

void init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Bresenham");

	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 400, 0, 400);
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
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 0.2);
	glPointSize(2);
	glBegin(GL_POINTS);
	Bresenham_Circle(200, 200, 50);
	glEnd();
	glFlush();
}
int main(int argc, char** argv)
{
	init(argc, argv);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}