#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

GLsizei winWidth = 600, winHeight = 600;
GLint nVerts = 12;//点的个数
GLfloat tx = 0, ty = 1, tz = 3;//存储要平移的距离
GLfloat angle = 60;//旋转角度
GLfloat scale = 2.0;//缩放比例
typedef GLfloat M4[4][4];
M4 matComposite;
class pt3D { public: GLfloat x, y, z; };
pt3D verts[] = {
	{ 0.0, 1.0, 0.0 },{ -1.0, -1.0, 1.0 },{ 1.0, -1.0, 1.0 },
	{ 0.0, 1.0, 0.0 },{ 1.0, -1.0, 1.0 },{ 1.0, -1.0, -1.0 },
	{ 0.0, 1.0, 0.0 },{ 1.0, -1.0, -1.0 },{ -1.0, -1.0, -1.0 },
	{ 0.0, 1.0, 0.0 },{ -1.0, -1.0, -1.0 },{ -1.0, -1.0, 1.0 }
};//存放三维物体的各个点坐标，由于有4个三角形面，所以有12个点，设置顶点一致就好，拼接三角形，底面不做绘制
pt3D resultVerts[12];//存放变换后的矩阵，即最新的点坐标
class color { public: GLfloat r, g, b; };
color colors[] = {
	{ 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0, 0.0, 1.0 },{ 1.0, 1.0, 0.0 }
};//存放每个面的颜色

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_PROJECTION);
}
void m4SetIdentity(M4 matIdentity4x4)
{
	GLint col, row;
	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++) {
			matIdentity4x4[row][col] = (row == col);
		}
	}
}
void m4PreMultiply(M4 m1, M4 m2)
{
	GLint row, col;
	M4 matTemp;
	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++) {
			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col] + m1[row][3] * m2[3][col];
		}
	}
	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++) {
			m2[row][col] = matTemp[row][col];
		}
	}
}
void translate3D(GLfloat tx, GLfloat ty, GLfloat tz)
{
	M4 matTranslate3D;
	m4SetIdentity(matTranslate3D);
	matTranslate3D[0][3] = tx;
	matTranslate3D[1][3] = ty;
	matTranslate3D[2][3] = tz;
	m4PreMultiply(matTranslate3D, matComposite);
}
void transformVerts3D()
{
	GLint k;
	for (k = 0; k < nVerts; k++) {
		resultVerts[k].x = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2] * verts[k].z + matComposite[0][3];
		resultVerts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2] * verts[k].z + matComposite[1][3];
		resultVerts[k].z = matComposite[2][0] * verts[k].x + matComposite[2][1] * verts[k].y + matComposite[2][2] * verts[k].z + matComposite[2][3];
	}
}

//画一个三棱锥，每个面设不同的颜色
void draw(pt3D *mat)
{
	int j;
	for (int i = 0; i < 4; i++) {
		glColor3f(colors[i].r, colors[i].g, colors[i].b);
		for (j = i * 3; j < i * 3 + 3; j++) {
			glVertex3f(mat[j].x, mat[j].y, mat[j].z);
		}
	}
}
void displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);//画坐标轴，可以省略，主要是为了看旋转变化
	glColor3f(1.0, 0.0, 0.0);//y轴红色
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);//x轴绿色
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 3);//z轴蓝色
	glEnd();
	glBegin(GL_TRIANGLES);                          // 绘制三角形      
	draw(verts);
	glEnd();
	glLoadIdentity();//不可以省略，否则后面对其它三维物体的变换也会发生在上面已经绘制的物体中
	GLfloat scaleBack = 1 / scale;
	glRotatef(angle, 0.0, 1.0, 0.0);
	glScalef(1.0, scale, 1.0);
	//GLfloat tx = 0, ty = 1.0, tz = 3;
	m4SetIdentity(matComposite);
	translate3D(tx, ty, tz);
	transformVerts3D();
	glBegin(GL_TRIANGLES);
	draw(resultVerts);
	glEnd();
	glScalef(1.0, scaleBack, 1.0);
	glLoadIdentity();
	glFlush();
}
/*
键盘设置，下面的还可以改善：当旋转或平移到一定数值时，回到原始状态
*/
void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:ty += 0.1; break;
	case GLUT_KEY_DOWN:ty -= 0.1; break;
	case GLUT_KEY_LEFT:tz += 0.1; break;
	case GLUT_KEY_RIGHT:tz -= 0.1; break;
	// F1 向上拉升
	case GLUT_KEY_F1:scale += 0.1; break;
	// F2 向下收缩
	case GLUT_KEY_F2:scale -= 0.1; break;
	// F3 绕Z轴旋转
	case GLUT_KEY_F3:angle += 10; break;
	// F4 复原
	case GLUT_KEY_F4:tx = 0; ty = 1; tz = 3; angle = 60; scale = 2; break;//回到原始状态
	default:break;
	}
	displayFunc();
}
void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("3D");
	init();
	glutDisplayFunc(displayFunc);
	glutSpecialFunc(processSpecialKeys);
	glutMainLoop();
}