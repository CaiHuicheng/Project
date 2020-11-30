#include <GL/glut.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4
#define INCLINEWIDTH 1
#define DESCLINEWIDTH 2
#define SOLIDLINE 3
#define BROKENLINE 4
#define STRAITLINE 1
#define CURVEDLINE 2
#define CURVEDSURFACE 3
#define OTHER 4
#define PERSPECTIVE 1
#define ORTHO 2
class Point3f
{
public:
	GLfloat x, y, z;
	Point3f() { x = y = z = 0; }
	Point3f(GLfloat tx, GLfloat ty, GLfloat tz) {
		x = tx;
		y = ty;
		z = tz;
	}
	Point3f subtract(Point3f p) {
		return Point3f(this->x - p.x, this->y - p.y, this->z - p.z);
	}
};

class LineSegment {
public:

	Point3f p1, p2, s;
	LineSegment() {  }
	LineSegment(Point3f tp1, Point3f tp2) {
		p1 = tp1;
		p2 = tp2;
		s = p1.subtract(p2);
	}
	LineSegment(Point3f s) {
		this->s = s;
	}
	LineSegment xmutiply(LineSegment line) {
		Point3f a = this->s, b = line.s;
		GLfloat tx = a.y*b.z - a.z*b.y;
		GLfloat ty = a.z*b.x - a.x*b.z;
		GLfloat tz = a.x*b.y - a.y*b.x;
		return LineSegment(Point3f(tx, ty, tz));
	}
	GLfloat abs() {
		return sqrtf(s.x*s.x + s.y*s.y + s.z*s.z);
	}
	GLfloat point2line(Point3f p) {
		LineSegment mm = LineSegment(p, p1);
		LineSegment t = this->xmutiply(mm);
		return t.abs() / this->abs();
	}
	GLfloat point2line(GLfloat* p) {
		return this->point2line(Point3f(p[0], p[1], p[2]));
	}
};
int model = STRAITLINE;
int lineWidth = 1;
int lineModel = STRAITLINE;
int view = ORTHO;
GLfloat rotateX = 0, rotateY = 0, rotateZ = 0, rotateAngle = 0.17;
GLfloat translatedX = 0, translatedY = 0, translatedZ = 0;
GLfloat scaleX = 1, scaleY = 1, scaleZ = 1;
GLfloat red = 1, green = 0, blue = 0;
int leftButtonDown = 0;
GLfloat oldx = 0, oldy = 0;
GLfloat deviation = 0.05;
GLfloat *cp;
int grab = 0;
GLfloat translate = 0.07;
GLfloat rotate = 0.01;
GLfloat scale = 0.1;

//直线
GLfloat ctrlPts1[2][3]{ { -1, 1, 0.0 },{ 1, 1, 0.0 } };
//曲线
GLfloat ctrlPts2[4][3] = { { -1, -1, 0.0 },{ -1, 1, 0.0 },
{ 1, 1, 0.0 },{ 1, -1, 0.0 } };
//曲面
GLfloat ctrlPts3[4][4][3] = {
	{ { -1.5, -1.5,  4.0 },{ -0.5, -1.5,  2.0 },
	{ -0.5, -1.5, -1.0 },{ 1.5, -1.5,  2.0 } },
	{ { -1.5, -0.5,  1.0 },{ -0.5, -0.5,  3.0 },
	{ 0.5, -0.5,  0.0 },{ 1.5, -0.5, -1.0 } },
	{ { -1.5,  0.5,  4.0 },{ -0.5,  0.5,  0.0 },
	{ 0.5,  0.5,  3.0 },{ 1.5,  0.5,  4.0 } },
	{ { -1.5,  1.5, -2.0 },{ -0.5,  1.5, -2.0 },
	{ 0.5,  1.5,  0.0 },{ 1.5,  1.5, -1.0 } }
};
/*  Set initial size of the display window.  */
GLsizei winWidth = 600, winHeight = 600;

/*  Set size of world-coordinate clipping window.  */
GLfloat xwcMin = -50.0, xwcMax = 50.0;
GLfloat ywcMin = -50.0, ywcMax = 50.0;

void init(void)
{
	/*  Set color of display window to white.  */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	GLfloat *p = &ctrlPts3[0][0][0];


}
class wcPt3D {
private:
	GLfloat x, y, z;
public:
	wcPt3D() {
		x = y = z = 0.0;
	}
	void setCoords(GLfloat xCoord, GLfloat yCoord, GLfloat zCoord) {
		x = xCoord;
		y = yCoord;
		z = zCoord;
	}
	GLfloat getx() const { return x; }
	GLfloat gety() const { return y; }
	GLfloat getz() const { return z; }
};

wcPt3D fixedPt = wcPt3D();

typedef GLfloat Matrix4x4[4][4];
void matrix4x4SetIdentity(Matrix4x4 matIdent4x4) {
	GLint row, col;
	for (row = 0; row < 4; row++)
		for (col = 0; col < 4; col++)    matIdent4x4[row][col] = (row == col);
}

//自定义平移函数  
void translate3D(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat * ctrlPts, int nPts, int stride) {
	Matrix4x4 matTransl3D;
	matrix4x4SetIdentity(matTransl3D);
	matTransl3D[0][3] = tx;
	matTransl3D[1][3] = ty;
	matTransl3D[2][3] = tz;
	int size = nPts * stride;
	for (int i = 0; i < size; i += stride)
	{
		for (int j = 0; j < 3; j++)
		{
			ctrlPts[i + j] += matTransl3D[j][3];
		}
	}
}

//自定义旋转函数  
void rotate3D(GLfloat e, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat * ctrlPts, int nPts, int stride)
{
	Matrix4x4 matRotate3D;
	matrix4x4SetIdentity(matRotate3D);
	int size = nPts * stride;
	if (rx == 1 && ry == 0 && rz == 0 && e != 0)
	{
		matRotate3D[0][0] = 1;
		matRotate3D[1][1] = cos(e);
		matRotate3D[1][2] = sin(e);
		matRotate3D[2][1] = -sin(e);
		matRotate3D[2][2] = cos(e);
		for (int i = 0; i < size; i += stride)
		{
			ctrlPts[i + 0] = matRotate3D[0][0] * ctrlPts[i + 0];
			ctrlPts[i + 1] = matRotate3D[1][1] * ctrlPts[i + 1] + matRotate3D[1][2] * ctrlPts[i + 2];
			ctrlPts[i + 2] = matRotate3D[2][1] * ctrlPts[i + 1] + matRotate3D[2][2] * ctrlPts[i + 2];
		}
	}
	else if (rx == 0 && ry == 1 && rz == 0 && e != 0)
	{
		matRotate3D[0][0] = cos(e);
		matRotate3D[0][2] = -sin(e);
		matRotate3D[1][1] = 1;
		matRotate3D[2][0] = sin(e);
		matRotate3D[2][2] = cos(e);
		for (int i = 0; i < size; i += stride)
		{
			ctrlPts[i + 0] = matRotate3D[0][0] * ctrlPts[i + 0] + matRotate3D[0][2] * ctrlPts[i + 2];
			ctrlPts[i + 1] = matRotate3D[1][1] * ctrlPts[i + 1];
			ctrlPts[i + 2] = matRotate3D[2][0] * ctrlPts[i + 0] + matRotate3D[2][2] * ctrlPts[i + 2];
		}
	}
	else if (rx == 0 && ry == 0 && rz == 1 && e != 0)
	{
		matRotate3D[0][0] = cos(e);
		matRotate3D[0][1] = -sin(e);
		matRotate3D[1][0] = sin(e);
		matRotate3D[1][1] = cos(e);
		matRotate3D[2][2] = 1;
		for (int i = 0; i < size; i += stride)
		{
			ctrlPts[i + 0] = matRotate3D[0][0] * ctrlPts[i + 0] + matRotate3D[0][1] * ctrlPts[i + 1];
			ctrlPts[i + 1] = matRotate3D[1][0] * ctrlPts[i + 0] + matRotate3D[1][1] * ctrlPts[i + 1];
			ctrlPts[i + 2] = matRotate3D[2][2] * ctrlPts[i + 2];
		}
	}



}

//自定义缩放函数  
void scale3D(GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt, GLfloat * ctrlPts, int nPts, int stride) {
	Matrix4x4 matScale3D;
	matrix4x4SetIdentity(matScale3D);
	matScale3D[0][0] = sx;
	matScale3D[0][3] = (1 - sx) * fixedPt.getx();
	matScale3D[1][1] = sy;
	matScale3D[1][3] = (1 - sy) * fixedPt.gety();
	matScale3D[2][2] = sz;
	matScale3D[2][3] = (1 - sz) * fixedPt.getz();
	int size = nPts * stride;
	for (int i = 0; i < size; i += stride)
	{
		ctrlPts[i + 0] = matScale3D[0][0] * ctrlPts[i + 0] + matScale3D[0][3] * ctrlPts[i + 3];
		ctrlPts[i + 1] = matScale3D[1][1] * ctrlPts[i + 1] + matScale3D[1][3] * ctrlPts[i + 3];
		ctrlPts[i + 2] = matScale3D[2][2] * ctrlPts[i + 2] + matScale3D[2][3] * ctrlPts[i + 3];
	}
}
void drawLine()
{
	glBegin(GL_LINES);
	glVertex3fv(ctrlPts1[0]);                      // Specify line-segment geometry.
	glVertex3fv(ctrlPts1[1]);
	glEnd();
	glBegin(GL_POINTS);
	glVertex3fv(ctrlPts1[0]);                      // Specify line-segment geometry.
	glVertex3fv(ctrlPts1[1]);
	glEnd();
}
void drawCruvedLine()
{
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *ctrlPts2);
	glEnable(GL_MAP1_VERTEX_3);

	GLint k;

	glColor3f(red, green, blue);           //  Set line color to blue.
	glBegin(GL_LINE_STRIP);             //  Generate Bezier "curve".
	for (k = 0; k <= 50; k++)
		glEvalCoord1f(GLfloat(k) / 50.0);
	glEnd();


	glColor3f(1, 0, 0);             //  Set point color to red.
									//glPointSize(5.0);                   //  Set point size to 5.0.
	glBegin(GL_POINTS);                 //  Plot control points.
	for (k = 0; k < 4; k++)
		glVertex3fv(ctrlPts2[k]);
	glEnd();

}
void drawCruvedSurface()
{
	//计算曲面
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4,
		0.0, 1.0, 12, 4, &ctrlPts3[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	GLint k, j;
	//画出曲面
	for (k = 0; k <= 8; k++)
	{
		glBegin(GL_LINE_STRIP);  // Generate Bezier surface lines.
		for (j = 0; j <= 40; j++)
			glEvalCoord2f(GLfloat(j) / 40.0, GLfloat(k) / 8.0);
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (j = 0; j <= 40; j++)
			glEvalCoord2f(GLfloat(k) / 8.0, GLfloat(j) / 40.0);
		glEnd();
	}

	//画出控制点
	glPointSize(5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (j = 0; j < 4; j++)
	{
		for (k = 0; k < 4; k++)
			glVertex3fv(ctrlPts3[j][k]);
	}
	glEnd();
}
void drawOther()
{

}

//显示函数
void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(red, green, blue);
	glLineWidth(lineWidth);
	glPointSize(5);
	wcPt3D p0;

	switch (lineModel) {
	case SOLIDLINE:
		glDisable(GL_LINE_STIPPLE);
		break;
	case BROKENLINE:
		glLineStipple(1, 0xFFF2);
		glEnable(GL_LINE_STIPPLE);
		break;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (view) {
	case ORTHO:
		glOrtho(-5, 5, -5, 5, -5, 5);
		gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
		break;

	case PERSPECTIVE:
		gluPerspective(70, 1, 5, 15);
		gluLookAt(0, 0, 10, 0, 0, -1, 0, 1, 0);
		break;
	}
	switch (model) {
	case STRAITLINE:
		translate3D(translatedX, translatedY, translatedZ, &ctrlPts1[0][0], 2, 3);
		scale3D(scaleX, scaleY, scaleZ, p0, &ctrlPts1[0][0], 2, 3);
		rotate3D(rotateAngle*rotateX, 1, 0, 0, &ctrlPts1[0][0], 2, 3);
		rotate3D(rotateAngle*rotateY, 0, 1, 0, &ctrlPts1[0][0], 2, 3);
		rotate3D(rotateAngle*rotateZ, 0, 0, 1, &ctrlPts1[0][0], 2, 3);
		drawLine();
		break;
	case CURVEDLINE:
		translate3D(translatedX, translatedY, translatedZ, &ctrlPts2[0][0], 4, 3);
		scale3D(scaleX, scaleY, scaleZ, p0, &ctrlPts2[0][0], 4, 3);
		rotate3D(rotateAngle*rotateX, 1, 0, 0, &ctrlPts2[0][0], 4, 3);
		rotate3D(rotateAngle*rotateY, 0, 1, 0, &ctrlPts2[0][0], 4, 3);
		rotate3D(rotateAngle*rotateZ, 0, 0, 1, &ctrlPts2[0][0], 4, 3);
		drawCruvedLine();
		break;
	case CURVEDSURFACE:
		translate3D(translatedX, translatedY, translatedZ, &ctrlPts3[0][0][0], 16, 3);
		scale3D(scaleX, scaleY, scaleZ, p0, &ctrlPts3[0][0][0], 16, 3);
		rotate3D(rotateAngle*rotateX, 1, 0, 0, &ctrlPts3[0][0][0], 16, 3);
		rotate3D(rotateAngle*rotateY, 0, 1, 0, &ctrlPts3[0][0][0], 16, 3);
		rotate3D(rotateAngle*rotateZ, 0, 0, 1, &ctrlPts3[0][0][0], 16, 3);
		drawCruvedSurface();
		break;
	}
	//glPopMatrix();
	glFlush();
	translatedX = translatedY = translatedZ = 0;
	rotateX = rotateY = rotateZ = 0;
	scaleX = scaleY = scaleZ = 1;
}
//窗口改变
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	/*  Maintain an aspect ratio of 1.0.  */
	glViewport(0, 0, newHeight, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (view) {
	case ORTHO:
		glOrtho(-5, 5, -5, 5, -5, 5);
		break;

	case PERSPECTIVE:
		gluPerspective(70, 1, 1, 800);
		break;
	}
	//gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);

	glClear(GL_COLOR_BUFFER_BIT);
}


LineSegment GetSelectionRay(int mouse_x, int mouse_y) {

	// 获取 Model-View、Projection 矩阵 & 获取Viewport视区

	GLdouble    modelview[16];

	GLdouble    projection[16];

	GLint       viewport[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble world_x, world_y, world_z;

	mouse_y = winHeight - mouse_y;

	// 获取近裁剪面上的交点

	gluUnProject((GLdouble)mouse_x, (GLdouble)mouse_y, 0.0,

		modelview, projection, viewport,

		&world_x, &world_y, &world_z);
	printf("World coords at z=0.0 are (%f, %f, %f)\n",
		world_x, world_y, world_z);

	Point3f near_point(world_x, world_y, world_z);

	// 获取远裁剪面上的交点

	gluUnProject((GLdouble)mouse_x, (GLdouble)mouse_y, 1.0,

		modelview, projection, viewport,

		&world_x, &world_y, &world_z);
	printf("World coords at z=1.0 are (%f, %f, %f)\n",
		world_x, world_y, world_z);

	Point3f far_point(world_x, world_y, world_z);

	return LineSegment(near_point, far_point);

}

bool intersect(LineSegment line) {
	bool flag = false;
	GLfloat x = line.p1.x;
	GLfloat y = line.p1.y;

	GLfloat tx, ty, tz, dx, dy;
	switch (model) {
	case STRAITLINE:
		if (view == ORTHO) {
			for (int i = 0; i <= 1; i++) {
				tx = ctrlPts1[i][0], ty = ctrlPts1[i][1], tz = ctrlPts1[i][2];
				cp = ctrlPts1[i];
				dx = fabs(tx - x), dy = fabs(ty - y);
				if (dx < deviation && dy < deviation) {
					flag = true;
					break;
				}
			}
		}
		else if (view == PERSPECTIVE) {
			for (int i = 0; i <= 1; i++) {
				cp = ctrlPts1[i];
				GLfloat t = line.point2line(ctrlPts1[i]);
				if (t<deviation) {
					flag = true;
					break;
				}
			}
		}
		break;
	case CURVEDLINE:
		if (view == ORTHO) {
			for (int i = 0; i <= 3; i++) {
				tx = ctrlPts2[i][0], ty = ctrlPts2[i][1], tz = ctrlPts2[i][2];
				cp = ctrlPts2[i];
				dx = fabs(tx - x), dy = fabs(ty - y);
				if (dx < deviation && dy < deviation) {
					flag = true;
					break;
				}
			}
		}
		else if (view == PERSPECTIVE) {
			for (int i = 0; i <= 3; i++) {
				cp = ctrlPts2[i];
				if (line.point2line(ctrlPts2[i])<deviation) {
					flag = true;
					break;
				}
			}
		}
		break;
	case CURVEDSURFACE:
		if (view == ORTHO) {
			for (int i = 0; i <= 3; i++) {
				for (int k = 0; k <= 3; k++) {
					tx = ctrlPts3[i][k][0], ty = ctrlPts3[i][k][1], tz = ctrlPts3[i][k][2];
					cp = ctrlPts3[i][k];
					dx = fabs(tx - x), dy = fabs(ty - y);
					if (dx < deviation && dy < deviation) {
						flag = true;
						goto out;
					}
				}
			}
		}
		else if (view == PERSPECTIVE) {
			for (int i = 0; i <= 3; i++) {
				for (int j = 0; j <= 3; j++) {
					cp = ctrlPts3[i][j];
					if (line.point2line(ctrlPts3[i][j])<deviation) {
						flag = true;
						goto out;
					}
				}
			}
		}

		break;
	}
out:
	return flag;
}
//鼠标点击事件
void mouse(int button, int state, int x, int y)
{

	LineSegment line;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			line = GetSelectionRay(x, y);
			leftButtonDown = 1;
			oldx = line.p1.x, oldy = line.p1.y;
			if (intersect(line)) {
				grab = true;

			}
		}
		else if (state == GLUT_UP) {
			grab = false;
		}
		break;
	case 3:
		//if(state=0)
		scaleX = scaleY = scaleZ = 1 + scale;
		break;
	case 4:
		//if(state=0)
		scaleX = scaleY = scaleZ = 1 - scale;
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
//鼠标移动
void motion(int x, int y)
{

	if (grab) {
		LineSegment line = GetSelectionRay(x, y);
		GLfloat tx = line.p1.x, ty = line.p1.y;
		GLfloat dx = tx - oldx, dy = ty - oldy;
		oldx = tx, oldy = ty;
		cp[0] += dx, cp[1] += dy;

	}
	glutPostRedisplay();
}
//特殊按键
void ProcessSpecialKeyboead(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		translatedY += translate;
		break;
	case GLUT_KEY_DOWN:
		translatedY -= translate;
		break;
	case GLUT_KEY_LEFT:
		translatedX -= translate;
		break;
	case GLUT_KEY_RIGHT:
		translatedX += translate;
		break;
	}
	glutPostRedisplay();
}
//普通按键
void keybord(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
		rotateX = 1;
		break;
	case 'a':
		rotateX = -1;
		break;
	case 'w':
		rotateY = 1;
		break;
	case 's':
		rotateY = -1;
		break;
	case 'e':
		rotateZ = 1;
		break;
	case 'd':
		rotateZ = -1;
		break;

	}
	glutPostRedisplay();
}
//鼠标移动事件
void passiveMotion(int x, int y)
{
	glutPostRedisplay();
}
//菜单处理
void processMenuEvents(int option)
{
	glutPostRedisplay();
}
void processModelEvents(int option)
{
	model = option;
	glutPostRedisplay();
}
void processColorMenuEvents(int option)
{
	switch (option) {
	case RED:
		red = 1.0, green = 0.0, blue = 0.0;
		break;
	case GREEN:
		red = 0.0, green = 1.0, blue = 0.0;
		break;
	case BLUE:
		red = 0.0, green = 0.0, blue = 1.0;
		break;
	}
	glutPostRedisplay();
}
void processLineMenuEvents(int option)
{
	switch (option) {
	case INCLINEWIDTH:
		lineWidth++;
		break;
	case DESCLINEWIDTH:
		if (lineWidth > 1)
			lineWidth--;
		break;
	case SOLIDLINE:
	case BROKENLINE:
		lineModel = option;
		break;
	}
	glutPostRedisplay();
}
void processViewMenuEvents(int option)
{
	view = option;
	glutPostRedisplay();
}
void addMenuItem()
{
	int modelMenu = glutCreateMenu(processModelEvents);
	glutAddMenuEntry("直线", STRAITLINE);
	glutAddMenuEntry("曲线", CURVEDLINE);
	glutAddMenuEntry("网格", CURVEDSURFACE);
	glutAddMenuEntry("其他", OTHER);
	int lineMenu = glutCreateMenu(processLineMenuEvents);
	glutAddMenuEntry("加粗线宽", INCLINEWIDTH);
	glutAddMenuEntry("减少线宽", DESCLINEWIDTH);
	glutAddMenuEntry("实线", SOLIDLINE);
	glutAddMenuEntry("虚线", BROKENLINE);
	int colorMenu = glutCreateMenu(processColorMenuEvents);
	glutAddMenuEntry("红色", RED);
	glutAddMenuEntry("绿色", GREEN);
	glutAddMenuEntry("蓝色", BLUE);
	int viewMenu = glutCreateMenu(processViewMenuEvents);
	glutAddMenuEntry("平行视角", PERSPECTIVE);
	glutAddMenuEntry("透视视角", ORTHO);
	// 创建菜单并告诉GLUT，processMenuEvents处理菜单事件。
	int menu = glutCreateMenu(processMenuEvents);

	//给菜单增加条目
	glutAddSubMenu("画图模式", modelMenu);
	glutAddSubMenu("颜色定义", colorMenu);
	glutAddSubMenu("线属性", lineMenu);
	glutAddSubMenu("视图", viewMenu);

	// 把菜单和鼠标右键关联起来。
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("小型图形软件系统");

	init();

	glutDisplayFunc(displayFcn);//注册图形显示回调函数
	glutReshapeFunc(winReshapeFcn);//注册改变窗口回调函数

	glutMouseFunc(mouse);//注册鼠标点击事件回调函数
	glutMotionFunc(motion);//注册鼠标移动事件回调函数
						   //glutPassiveMotionFunc(passiveMotion);
	addMenuItem();

	glutSpecialFunc(ProcessSpecialKeyboead);//注册特殊键盘事件回调函数
	glutKeyboardFunc(keybord);//注册普通按键事件回调函数
	glutMainLoop();
}