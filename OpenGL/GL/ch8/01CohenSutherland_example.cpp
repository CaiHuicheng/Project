#include<GL/glut.h>
#include<stdio.h>
#include<math.h> 

class Point
{
public:
	float x, y;
};

bool hasLine = true, cut = false;
float offset = 10;
int winWidth = 400, winHeight = 300;
Point clippingWindow[4], line[2], bound[4][2], inside[2];// 用于记录线段line位于裁剪窗口内的两个端点

														 // 初始化裁剪窗口的四个顶点坐标
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

// 更新边界
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

// 初始化line
void initLine(void)
{
	line[0].x = 0;
	line[0].y = 0;

	line[1].x = 0;
	line[1].y = 0;

}

// 用指定的颜色画线段
void drawLine(Point p1, Point p2, float red, float green, float blue)
{
	glLineWidth(5);
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
}

// 生成端点的区域码
int encode(Point point, Point clippingWindow[4])
{
	int code = 0x0;

	if (point.x < clippingWindow[1].x)
		code = code | 0x1;
	if (point.x > clippingWindow[3].x)
		code = code | 0x2;
	if (point.y < clippingWindow[1].y)
		code = code | 0x4;
	if (point.y > clippingWindow[3].y)
		code = code | 0x8;

	return code;
}

// 求line1、line2的交点
Point getIntersection(Point line1[2], Point line2[2])
{
	float dx1 = line1[1].x - line1[0].x, dy1 = line1[1].y - line1[0].y;
	float dx2 = line2[1].x - line2[0].x, dy2 = line2[1].y - line2[0].y;
	Point intersection;

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
void cohenSutherland(Point clippingWindow[4], Point line[2], int mode)
{
	int code0 = encode(line[0], clippingWindow);
	int code1 = encode(line[1], clippingWindow);

	if (code0 == 0 && code1 == 0)   // 如果直线在裁剪窗口里面，则直接绘制直线
		drawLine(line[0], line[1], 0, 1, 0);
	else
	{
		Point inside[2];   // 用于记录线段line位于裁剪窗口内的两个端点
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
						drawLine(inside[0], inside[1], 1, 0, 0);
					return;
				}
				else   // 两个端点都在边界的内侧
					continue;
			}
			else   // 两个端点在边界的两侧
			{
				Point p = getIntersection(inside, bound[i]);
				if (p.x != NAN && p.y != NAN)
				{
					if (current0 == 1)   // 端点inside[0]在边界的外侧，则用交点p换掉端点inside[0]
					{
						if (mode == 0)
							drawLine(p, inside[0], 1, 0, 0);
						inside[0] = p;
						code0 = encode(inside[0], clippingWindow);
					}
					else   // 端点inside[1]在边界的外侧，则用交点p换掉端点inside[1]
					{
						if (mode == 0)
							drawLine(p, inside[1], 1, 0, 0);
						inside[1] = p;
						code1 = encode(inside[1], clippingWindow);
					}
				}
			}
		}

		// 绘制裁剪窗口内的线段
		drawLine(inside[0], inside[1], 0, 1, 0);
	}
}

// 绘制裁剪窗口和线段
void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawClippingWindow();
	cohenSutherland(clippingWindow, line, 0);
	glFlush();
}

// 绘制裁剪窗口和线段
void display2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawClippingWindow();
	cohenSutherland(clippingWindow, line, 1);
	glFlush();
}

// 平移裁剪窗口
void translateClippingWindow(float tx, float ty)
{
	for (int i = 0; i < 4; i++)
	{
		clippingWindow[i].x += tx;
		clippingWindow[i].y += ty;
	}
	updateBound();
}

// 缩放裁剪窗口
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
		if (hasLine)
		{
			line[0].x = x;
			line[0].y = y;
			hasLine = false;
			cut = false;
		}
		else
		{
			line[1].x = x;
			line[1].y = y;
			hasLine = true;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && hasLine)   // 右键执行Cohen-Sutherland算法
	{
		cut = true;
		glutPostRedisplay();
	}
	if (button == 3)   // 向上滑动滚轮，放大裁剪窗口
	{
		cut = false;
		scaleClippingWindow(1.1, 1.1);
		glutPostRedisplay();
	}
	if (button == 4)   // 向下滑动滚轮，缩小裁剪窗口
	{
		cut = false;
		scaleClippingWindow(0.9, 0.9);
		glutPostRedisplay();
	}
}

void passiveMotionEvent(int clickX, int clickY)
{
	if (!hasLine)
	{
		line[1].x = clickX - (winWidth / 2);
		line[1].y = (winHeight / 2) - clickY;

		glutPostRedisplay();
	}
}

void keyEvent(unsigned char key, int clickX, int clickY)
{
	cut = false;

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

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	//form1
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Cohen Sutherland - 控制窗口");
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	initClippingWindow();
	updateBound();
	initLine();
	glutDisplayFunc(display1);
	glutMouseFunc(mouseEvent);
	glutKeyboardFunc(keyEvent);
	glutPassiveMotionFunc(passiveMotionEvent);

	//form2
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Cohen Sutherland - 裁剪效果显示窗口");
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	initClippingWindow();
	updateBound();
	initLine();
	glutDisplayFunc(display2);

	glutMainLoop();
}