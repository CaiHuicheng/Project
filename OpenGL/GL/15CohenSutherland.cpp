#include<gl\glut.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>

class wcPt2D
{
public:
	GLfloat x, y;
};

const GLint winLeftBitCode = 0x01;
const GLint winRightBitCode = 0x02;
const GLint winBottomBitCode = 0x04;
const GLint winTopBitCode = 0x08;

int winWidth = 400, winHeight = 300;
GLint done = false, plotLine = true;
float offset = 10;

wcPt2D clippingWindow[4],win[2], line[2],bound[4][2];

inline GLint inside(GLint code) { return GLint(!code); }
inline GLint reject(GLint code1, GLint code2) { return GLint(code1&code2); }
inline GLint accept(GLint code1, GLint code2) { return GLint(!(code1 | code2)); }


// 初始化裁剪窗口的四个顶点坐标和winMin、winMax
void initClippingWindow(void)
{
	// 左上角
	win[0].x = clippingWindow[0].x = -100;
	win[0].y = clippingWindow[0].y = 100;

	// 左下角
	clippingWindow[1].x = -100;
	clippingWindow[1].y = -100;

	// 右下角
	clippingWindow[2].x = 100;
	clippingWindow[2].y = -100;

	// 右上角
	win[1].x = clippingWindow[3].x = 100;
	win[1].x  =clippingWindow[3].y = 100;
}

// 绘制裁剪窗口
void drawClippingWindow(void)
{
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++)
		glVertex2f(clippingWindow[i].x, clippingWindow[i].y);
	glEnd();
}

// 更新边界和winMin、winMax
void updateBound(void)
{
	// 由裁剪窗口的左上角顶点和左下角定点组成的线，即左边界
	bound[0][0] = clippingWindow[0];
	bound[0][1] = clippingWindow[1];

	// 右边界
	bound[1][0] = clippingWindow[2];
	bound[1][1] = clippingWindow[3];

	// 下边界
	bound[2][0] = clippingWindow[1];
	bound[2][1] = clippingWindow[2];

	// 上边界
	bound[3][0] = clippingWindow[0];
	bound[3][1] = clippingWindow[3];

	// 左上角
	win[0].x = clippingWindow[0].x;
	win[0].y = clippingWindow[0].y;

	// 右上角
	win[1].x = clippingWindow[3].x;
	win[1].x = clippingWindow[3].y;
}

GLubyte enCode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax) {
	GLubyte code = 0x00;
	if (pt.x < winMin.x) code = code | winLeftBitCode;
	if (pt.x > winMax.x) code = code | winRightBitCode;
	if (pt.y > winMin.y) code = code | winBottomBitCode;
	if (pt.y < winMax.y) code = code | winTopBitCode;
	return code;
}

void swapPts(wcPt2D *p1, wcPt2D *p2) {
	wcPt2D tmp;
	tmp = *p1; *p1 = *p2; *p2 = tmp;
}

void swapCodes(GLubyte *c1, GLubyte *c2) {
	GLubyte tmp;
	tmp = *c1; *c1 = *c2; *c2 = tmp;
}

//void setPixel(GLint xCoord, GLint yCoord) {
//	glBegin(GL_POINTS);
//	glVertex2i(xCoord, yCoord);
//	glEnd();
//}
void PlotLine(wcPt2D p1, wcPt2D p2,GLfloat red,GLfloat green,GLfloat blue) {
	glLineWidth(5);
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
}

//void lineBres(int x0, int y0, int xEnd, int yEnd) {
//	int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
//	int p = 2 * dy - dx;
//	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
//	int x, y;
//	if (x0 > xEnd) {
//		x = xEnd;
//		y = yEnd;
//		xEnd = 0;
//	}
//	else {
//		x = x0; y = y0;
//	}
//	setPixel(x, y);
//	while (x < xEnd) {
//		x++;
//		if (p < 0) {
//			p += twoDy;
//		}
//		else {
//			y++;
//			p += twoDyMinusDx;
//		}
//		setPixel(x, y);
//	}
//}

void lineClipCohSuth(wcPt2D winMin,wcPt2D winMax,wcPt2D p1,wcPt2D p2) {
	GLubyte code1, code2;
	GLfloat m;
	while (!done) {
		code1 = enCode(p1, winMin, winMax);
		code2 = enCode(p2, winMin, winMax);
		if (accept(code1, code2)) {
			done = true;
			plotLine = true;
		}
		else {
			if (reject(code1, code2)) {
				done = true;
			}
			else {
				if (inside(code1)) {
					swapPts(&p1, &p2);
					swapCodes(&code1, &code2);
				}
				if (p2.x != p1.x) {
					m = (p2.y - p1.y) / (p2.x - p2.y);
				}
				if (code1 & winLeftBitCode) {
					p1.y += (winMin.x - p1.x) *m;
					p1.x = winMin.x;
				}
				else {
					if (code1 & winRightBitCode) {
						p1.y += (winMax.x - p1.x)*m;
						p1.x = winMax.x;
					}
					else {
						if (code1&winBottomBitCode) {
							if (p2.x != p1.x) {
								p1.x += (winMin.y - p1.y)/m;
							}
							p1.y = winMin.y;
						}
						else {
							if (code1&winTopBitCode) {
								if (p2.x != p1.x) {
									p1.x += (winMax.y - p1.y) / m;
								}
								p1.y = winMax.y;
							}
						}
					}
				}
			}
		}
	}
	if (plotLine)
		PlotLine(p1, p2, 0, 1, 0);
}

void display_win() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawClippingWindow();
	lineClipCohSuth(win[0], win[1], line[0], line[1]);
	glFlush();
}

//平移剪裁窗口
void translateClippingWindow(GLfloat x, GLfloat y) {
	for (int i = 0; i <= 4; i++) {
		clippingWindow[i].x += x;
		clippingWindow[i].y += y;
	}
}

//缩放裁剪窗口
void scaleClippingWindow(float sx, float sy)
{
	float centerX = (clippingWindow[1].x + clippingWindow[3].x) / 2;
	float centerY = (clippingWindow[1].y + clippingWindow[3].y) / 2;

	translateClippingWindow(-centerX, -centerY);
	for (int i = 0; i < 4; i++)
	{
		clippingWindow[i].x *= sx;
		clippingWindow[i].y *= sy;
	}
	translateClippingWindow(centerX, centerY);

	updateBound();
}

void mouseEvent(int button, int state, int clickX, int clickY)
{
	float x = clickX - (winWidth / 2), y = (winHeight / 2) - clickY;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)   // 左键画线
	{
		if (plotLine)
		{
			line[0].x = x;
			line[0].y = y;
			plotLine = false;
			done = false;
		}
		else
		{
			line[1].x = x;
			line[1].y = y;
			plotLine = true;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && plotLine)   // 右键执行Cohen-Sutherland算法
	{
		done = true;
		glutPostRedisplay();
	}
	if (button == 3)   // 向上滑动滚轮，放大裁剪窗口
	{
		done = false;
		scaleClippingWindow(1.1, 1.1);
		glutPostRedisplay();
	}
	if (button == 4)   // 向下滑动滚轮，缩小裁剪窗口
	{
		done = false;
		scaleClippingWindow(0.9, 0.9);
		glutPostRedisplay();
	}
}

void passiveMotionEvent(int clickX, int clickY)
{
	if (!plotLine)
	{
		line[1].x = clickX - (winWidth / 2);
		line[1].y = (winHeight / 2) - clickY;

		glutPostRedisplay();
	}
}

void keyEvent(unsigned char key, int clickX, int clickY)
{
	done = false;

	float dx = 0, dy = 0;

	// w、a、s、d分别对应裁剪窗口的向上移动、向下移动、向左移动、向右移动操作
	if (key == 'w' || key == 'W')
		dy = offset;
	if (key == 's' || key == 'S')
		dy = -offset;
	if (key == 'a' || key == 'A')
		dx = -offset;
	if (key == 'd' || key == 'D')
		dx = offset;

	// Enter键：将裁剪窗口恢复回初始状态
	if (key == 13)
		initClippingWindow();
	translateClippingWindow(dx, dy);
	glutPostRedisplay();
}

void init() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Cohen Sutherland");
	//设置显示窗口背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//设置世界坐标剪裁窗口的参数
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	initClippingWindow();
	updateBound();
}


void main(int argc, char**argv) {
	glutInit(&argc, argv);
	init();
	glutDisplayFunc(display_win);
	glutMouseFunc(mouseEvent);
	glutKeyboardFunc(keyEvent);
	glutPassiveMotionFunc(passiveMotionEvent);
	glutMainLoop();
}