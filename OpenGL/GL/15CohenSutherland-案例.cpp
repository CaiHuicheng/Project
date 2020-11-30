#include<gl\glut.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>

class wcPt2D
{
public:
	GLfloat x, y;
};

const GLint winLeftBitCode = 0x1;
const GLint winRightBitCode = 0x2;
const GLint winBottomBitCode = 0x4;
const GLint winTopBitCode = 0x8;

int winWidth = 400, winHeight = 300;
GLint done = false, plotLine = true;
float offset = 10;

wcPt2D clippingWindow[4], line[2],bound[4][2];

//inline GLint inside(GLint code) { return GLint(!code); }
//inline GLint reject(GLint code1, GLint code2) { return GLint(code1&code2); }
//inline GLint accept(GLint code1, GLint code2) { return GLint(!(code1 | code2)); }


// 初始化裁剪窗口的四个顶点坐标和winMin、winMax
void initClippingWindow(void)
{
	// 左上角
	clippingWindow[0].x = -100;
	clippingWindow[0].y = 100;

	// 左下角
	clippingWindow[1].x = -100;
	clippingWindow[1].y = -100;

	// 右下角
	clippingWindow[2].x = 100;
	clippingWindow[2].y = -100;

	// 右上角
	clippingWindow[3].x = 100;
	clippingWindow[3].y = 100;
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
}

// 生成端点的区域码
/*
GLubyte enCode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax) {
	GLubyte code = 0x00;
	if (pt.x < winMin.x) code = code | winLeftBitCode;
	if (pt.x > winMax.x) code = code | winRightBitCode;
	if (pt.y > winMin.y) code = code | winBottomBitCode;
	if (pt.y < winMax.y) code = code | winTopBitCode;
	return code;
}
*/
GLubyte enCode(wcPt2D pt, wcPt2D clippingWindow[4]) {
	GLubyte code = 0x00;
	if (pt.x < clippingWindow[1].x) code = code | winLeftBitCode;
	if (pt.x > clippingWindow[2].x) code = code | winRightBitCode;
	if (pt.y > clippingWindow[3].y) code = code | winBottomBitCode;
	if (pt.y < clippingWindow[4].y) code = code | winTopBitCode;
	return code;
}

// 初始化line
void initLine(void)
{
	line[0].x = 0;
	line[0].y = 0;
 
	line[1].x = 0;
	line[1].y = 0;
 
}


//void swapPts(wcPt2D *p1, wcPt2D *p2) {
//	wcPt2D tmp;
//	tmp = *p1; *p1 = *p2; *p2 = tmp;
//}

//void swapCodes(GLubyte *c1, GLubyte *c2) {
//	GLubyte tmp;
//	tmp = *c1; *c1 = *c2; *c2 = tmp;
//}

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


// 求line1、line2的交点
wcPt2D getIntersection(wcPt2D line1[2], wcPt2D line2[2])
{
	float dx1 = line1[1].x - line1[0].x, dy1 = line1[1].y - line1[0].y;
	float dx2 = line2[1].x - line2[0].x, dy2 = line2[1].y - line2[0].y;
	wcPt2D intersection;

	if (dx1 != 0 && dx2 != 0)   // 如果两条直线都有斜率
	{
		// 求直线的参数：y = ax + b
		float a1 = dy1 / dx1, b1 = line1[0].y - a1 * line1[0].x;
		float a2 = dy2 / dx2, b2 = line2[0].y - a2 * line2[0].x;

		intersection.x = (b2 - b1) / (a1 - a2);
		intersection.y = a1 * intersection.x + b1;
	}
	else if (dx1 == 0 && dx2 != 0)   // 如果line1垂直于x轴
	{
		float a2 = dy2 / dx2, b2 = line2[0].y - a2 * line2[0].x;

		intersection.x = line1[0].x;
		intersection.y = a2 * intersection.x + b2;
	}
	else if (dx1 != 0 && dx2 == 0)   // 如果line2垂直于x轴
	{
		float a1 = dy1 / dx1, b1 = line1[0].y - a1 * line1[0].x;

		intersection.x = line2[0].x;
		intersection.y = a1 * intersection.x + b1;
	}
	else   // 如果两条直线都垂直于x轴，也就是平行，那么无交点。（NAN = not a number）
	{
		intersection.x = NAN;
		intersection.y = NAN;
	}
	return intersection;
}

// Cohen-Sutherland线段裁剪算法
/*
void lineClipCohSuth(wcPt2D winMin,wcPt2D winMax,wcPt2D p1,wcPt2D p2,int mode) {
	GLubyte code1, code2;
	GLfloat m;
	wcPt2D insides[2];   // 用于记录线段line位于裁剪窗口内的两个端点
	insides[0] = p1;
	insides[1] = p2;
	while (!done) {
		code1 = enCode(p1, winMin, winMax);
		code2 = enCode(p2, winMin, winMax);
		if (accept(code1, code2)) {
			done = true;
			plotLine = true;
			PlotLine(p1, p2, 0, 1, 0);
		}
		else {
			if (reject(code1, code2)) {
				if(mode ==0)
					PlotLine(p1, p2, 1, 0, 0);
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
					wcPt2D p = getIntersection(insides, bound[0]);
					if (mode == 0)
						PlotLine(p1, insides[0], 1, 0, 0);
					p1.y += (winMin.x - p1.x) *m;
					p1.x = winMin.x;
				}
				else {
					if (code1 & winRightBitCode) {
						wcPt2D p = getIntersection(insides, bound[1]);
						if (mode == 0)
							PlotLine(p1, insides[0], 1, 0, 0);
						p1.y += (winMax.x - p1.x)*m;
						p1.x = winMax.x;
					}
					else {
						if (code1&winBottomBitCode) {
							wcPt2D p = getIntersection(insides, bound[2]);
							if (mode == 0)
								PlotLine(p1, insides[1], 1, 0, 0);
							if (p2.x != p1.x) {
								p1.x += (winMin.y - p1.y)/m;
							}
							p1.y = winMin.y;
						}
						else {
							if (code1&winTopBitCode) {
								wcPt2D p = getIntersection(insides, bound[3]);
								if (mode == 0)
									PlotLine(p1, insides[1], 1, 0, 0);
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
		PlotLine(insides[0], insides[1], 0, 1, 0);
}
*/
void lineClipCohSuth(wcPt2D clippingWindow[4], wcPt2D line[2], int mode)
{
	int code0 = enCode(line[0], clippingWindow);
	int code1 = enCode(line[1], clippingWindow);

	if (code0 == 0 && code1 == 0)   // 如果直线在裁剪窗口里面，则直接绘制直线
		/*done = true;
		plotLine = true;*/
		PlotLine(line[0], line[1], 0, 1, 0);
	else
	{
		wcPt2D inside[2];   // 用于记录线段line位于裁剪窗口内的两个端点
		inside[0] = line[0];
		inside[1] = line[1];

		// 4次循环分别代表4个边界处理：左、右、下、上
		for (int i = 0; i < 4; i++)
		{
			int temp = (int)pow(2, i);
			int current0 = (code0 & temp) >> i;
			int current1 = (code1 & temp) >> i;


			if (current0 == current1)   // 两个端点都在边界的同一侧
			{
				if (current0 == 1)   // 两个端点都在边界的外侧
				{
					if (mode == 0)
						PlotLine(inside[0], inside[1], 1, 0, 0);
					return;
				}
				else   // 两个端点都在边界的内侧
					continue;
			}
			else   // 两个端点在边界的两侧
			{
				wcPt2D p = getIntersection(inside, bound[i]);
				if (p.x != NAN && p.y != NAN)
				{
					if (current0 == 1)   // 端点inside[0]在边界的外侧，则用交点p换掉端点inside[0]
					{
						if (mode == 0)
							PlotLine(p, inside[0], 1, 0, 0);
						inside[0] = p;
						code0 = enCode(inside[0], clippingWindow);
					}
					else   // 端点inside[1]在边界的外侧，则用交点p换掉端点inside[1]
					{
						if (mode == 0)
							PlotLine(p, inside[1], 1, 0, 0);
						inside[1] = p;
						code1 = enCode(inside[1], clippingWindow);
					}
				}
			}
		}

		// 绘制裁剪窗口内的线段
		PlotLine(inside[0], inside[1], 0, 1, 0);
	}
}


void display_win() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawClippingWindow();
	lineClipCohSuth(clippingWindow, line,0);
	glFlush();
}

void displayClippingWindow() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawClippingWindow();
	lineClipCohSuth(clippingWindow, line, 1);
	glFlush();
}

//平移剪裁窗口
void translateClippingWindow(GLfloat x, GLfloat y) {
	for (int i = 0; i <= 4; i++) {
		clippingWindow[i].x += x;
		clippingWindow[i].y += y;
	}
	updateBound();
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
	//Form1
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Cohen Sutherland -- 控制窗口");
	//设置显示窗口背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//设置世界坐标剪裁窗口的参数
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	initClippingWindow();
	updateBound();
	initLine(); 
	glutDisplayFunc(display_win);
	glutMouseFunc(mouseEvent);
	glutKeyboardFunc(keyEvent);
	glutPassiveMotionFunc(passiveMotionEvent);

	//Form2
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Cohen Sutherland -- 显示窗口");
	//设置显示窗口背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//设置世界坐标剪裁窗口的参数
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	initClippingWindow();
	updateBound();
	initLine();
	glutDisplayFunc(displayClippingWindow);
}

//void ClippingWindowInit() {
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(50, 100);
//	glutInitWindowSize(winWidth, winHeight);
//	glutCreateWindow("Cohen Sutherland -- 显示窗口");
//	//设置显示窗口背景颜色
//	glClearColor(1.0, 1.0, 1.0, 0.0);
//	//设置世界坐标剪裁窗口的参数
//	glMatrixMode(GL_PROJECTION);
//	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
//	initClippingWindow();
//	updateBound();
//	initLine();
//
//}


void main(int argc, char**argv) {
	glutInit(&argc, argv);
	init();
	glutMainLoop();
}