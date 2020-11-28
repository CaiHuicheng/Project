#include<GL/glut.h>
#include<GL\GL.h>
#include<GLES3\gl3.h>
#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

#define PI 3.14159265358
//平移，绘制多边形，旋转，缩放
#define TRANSLATE 0
#define DRAWPOLYGON 1
#define ROTATE 2
#define SCALE 3

GLint tran_x, tran_y;
GLint _xtmp, _ytmp;//缩放变量
GLint mode = DRAWPOLYGON;

const GLint winWidth = 800;
const GLint winHeight = 640;

struct position{
	GLdouble x, y;
};

typedef GLfloat Matrix3x3[3][3];
Matrix3x3 matComposite;
vector<position> xy;
position tmp;
void DrawPolygon();
void dragmouse(int x, int y);
void myMouse(int button, int state, int x, int y);
void myKeyBoard(unsigned char key, int x, int y);
void myKeyBoardUp(unsigned char key, int x, int y);

//设置为单位矩阵
void matrix3x3SetIdentity(Matrix3x3 mat) {
	GLint row, col;
	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			mat[row][col] = (row == col);
		}
	}
}


void init() {
	//设置绘制窗口颜色为白色
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//清除窗口显示内容
	glClear(GL_COLOR_BUFFER_BIT);
	/*设置为投影类型描述和其他观察参数*/
	glPointSize(3.0f);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winWidth, winHeight,0);
	matrix3x3SetIdentity(matComposite);
}


//矩阵点乘
void matrixpreMultiply(Matrix3x3 m1, Matrix3x3 m2) {
	GLint row, col;
	Matrix3x3 tmp;
	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			tmp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col];
		}
	}
	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			m2[row][col] = tmp[row][col];
		}
	}
}

//平移
void translate2D(GLfloat tx, GLfloat ty) {
	Matrix3x3 matTransl;
	matrix3x3SetIdentity(matTransl);
	matTransl[0][2] = tx;
	matTransl[1][2] = ty;
	matrixpreMultiply(matTransl, matComposite);
}

//旋转
void rotate2D(GLint x, GLint y, GLfloat theta) {
	theta = theta / 180 * PI;
	Matrix3x3 matRot;
	matrix3x3SetIdentity(matRot);
	matRot[0][0] = cos(theta);
	matRot[0][1] = -sin(theta);
	matRot[0][2] = x*(1 - cos(theta)) + y*sin(theta);
	matRot[1][0] = sin(theta);
	matRot[1][1] = cos(theta);
	matRot[1][2] = y*(1 - cos(theta)) - x*sin(theta);
	matrixpreMultiply(matRot, matComposite);
}

//缩放
void scale2D(GLfloat sx, GLfloat sy, GLint x, GLint y) {
	Matrix3x3 matScale;
	matrix3x3SetIdentity(matScale);
	matScale[0][0] = sx;
	matScale[0][2] = (1 - sx)*x;
	matScale[1][1] = sy;
	matScale[1][2] = (1 - sy)*y;
	matrixpreMultiply(matScale, matComposite);
}
//绘制多边形
void DrawPolygon() {
	glPolygonMode(GL_BACK, GL_LINE);//设置反面为线性模式
	glPolygonMode(GL_FRONT, GL_LINE);//设置正面为线性模式
	glClear(GL_COLOR_BUFFER_BIT);//清除窗口显示内容
	glBegin(GL_POLYGON);
	for (unsigned int i = 0; i < xy.size(); i++) {
		glVertex2f(xy[i].x, xy[i].y);
	}
	glEnd();
	glFlush();
}


//复合矩阵
void transformVerts2D() {
	GLfloat tmp;
	for (int i = 0; i < xy.size(); i++) {
		tmp = matComposite[0][0] * xy[i].x + matComposite[0][1] * xy[i].y + matComposite[0][2];
		xy[i].y = matComposite[1][0] * xy[i].x + matComposite[1][1] * xy[i].y + matComposite[1][2];
		xy[i].x = tmp;
	}
	DrawPolygon();
	matrix3x3SetIdentity(matComposite);
}

//鼠标拖拽
void dragmouse(int x,int y) {
	float ssx = 1, ssy = 1;
	switch (mode)
	{
	case TRANSLATE:
		translate2D(x - tran_x, y - tran_y);
		transformVerts2D();
		tran_x = x;
		tran_y = y;
		break;
	case DRAWPOLYGON:
		break;
	case ROTATE:
		if (x <= _xtmp&&y >= +_ytmp) {
			rotate2D(tran_x, tran_y, -8);
		}
		else {
			rotate2D(tran_x, tran_y, 8);
		}
		transformVerts2D();
		_xtmp = x;
		_ytmp = y;
		break;

	case SCALE:
		//不等比缩放
		if (x > _xtmp) ssx += 0.01f;
		else if(x < _xtmp&&ssx>0) ssx -= 0.01f;
		if (y < _ytmp)ssy += 0.01f;
		else if (y > _ytmp&&ssy > 0) ssy -= 0.01f;
		////等比例缩放
		//if (x <= _xtmp&&y >= _ytmp) {
		//	ssx -= 0.01f;
		//	ssy -= 0.01f;
		//}
		//else {
		//	ssx += 0.01f;
		//	ssy += 0.01f;
		//}
		scale2D(ssx, ssy, tran_x, tran_y);
		transformVerts2D();
		_xtmp = x;
		_ytmp = y;
		break;

	default:
		break;
	}
}

//鼠标
void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN) {
		switch (mode)
		{
		case TRANSLATE:
			tran_x = x;
			tran_y = y; 
			break;
		case DRAWPOLYGON:
			tmp.x = x;
			tmp.y = y;
			xy.push_back(tmp);
			DrawPolygon();
			break;
		case ROTATE:
			tran_x = x;
			tran_y = y;
			xy.push_back(tmp);
			DrawPolygon();
			break;
		case SCALE:
			tran_x = x;
			tran_y = y;
			break;
		default:
			break;
		}
	}
}

//键盘
void myKeyBoard(unsigned char key, int x, int y) {
	//清空
	if (key == ' ') {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		xy.clear();
	}
}

void myKeyBoardUp(unsigned char key,int x,int y) {
	switch (key)
	{
	case 'q':
		mode = TRANSLATE;
		break;
	case 'w':
		mode = DRAWPOLYGON;
		break;
	case 'e':
		mode = ROTATE;
		break;
	case 'r':
		mode = SCALE;
		break;
	default:
		break;
	}
}

void myDisplay() {
	glFlush();
}
void myMenu(int id) {
	if (id == 0) mode = 0;
	else if (id == 1) mode = 1;
	else if (id == 2) mode = 2;
	else if (id == 3) mode = 3;
}


int main(int argc, char** argv) {
	//初始化
	glutInit(&argc, argv);
	//设置绘图模式
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(500, 300);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("二维图形的变换");
	int id = glutCreateMenu(myMenu);
	glutAddMenuEntry("平移", 0);
	glutAddMenuEntry("绘制多边形", 1); 
	glutAddMenuEntry("旋转", 2);
	glutAddMenuEntry("缩放", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutDisplayFunc(myDisplay);
	//鼠标监听回调函数
	glutMouseFunc(myMouse);
	//鼠标拖动
	glutMotionFunc(dragmouse);
	//键盘监听
	glutKeyboardFunc(myKeyBoard);
	//键盘弹起状态
	glutKeyboardUpFunc(myKeyBoardUp);
	glutMainLoop();
}