#include<GL/glut.h> 
#include<iostream> 
#include<stdio.h> 
#include<stdlib.h> 

using namespace std;

typedef struct
{
	float x, y, z;
}wcPt3D;
typedef enum

{
	Left, Right, Bottom, Top, Behind, Front
}Boundary;
int Inside(wcPt3D p, Boundary b, wcPt3D wMin, wcPt3D wMax)
{
	switch (b)
	{
	case Left:
		if (p.x<wMin.x) return (false);
		break;
	case Right:
		if (p.x>wMax.x) return (false);
		break;
	case Bottom:
		if (p.y<wMin.y) return (false);
		break;
	case Top:
		if (p.y>wMax.y) return (false);
		break;
	case Behind:
		if (p.z<wMin.z) return (false);
		break;
	case Front:
		if (p.z>wMax.z) return (false);
		break;
	}
	return true;
}

int Cross(wcPt3D p1, wcPt3D p2, Boundary b, wcPt3D wMin, wcPt3D wMax)
{
	if (Inside(p1, b, wMin, wMax) == Inside(p2, b, wMin, wMax))
		return (false);
	else
		return true;
}

wcPt3D Intersect(wcPt3D p1, wcPt3D p2, Boundary b, wcPt3D  wMin, wcPt3D wMax)
{
	wcPt3D iPt;
	float m1, m2, m3, m4, m5, m6;
	if (p1.x != p2.x)

	{
		m1 = (wMin.x - p1.x) / (p2.x - p1.x);
		m2 = (wMax.x - p1.x) / (p2.x - p1.x);
	}
	if (p1.y != p2.y)
	{
		m3 = (wMin.y - p1.y) / (p2.y - p1.y);
		m4 = (wMax.y - p1.y) / (p2.y - p1.y);
	}
	if (p1.z != p2.z)

	{
		m5 = (wMin.z - p1.z) / (p2.z - p1.z);
		m6 = (wMax.z - p1.z) / (p2.z - p1.z);
	}

	switch (b) {
	case Left:
		iPt.x = wMin.x;
		iPt.y = p1.y + (p2.y - p1.y)*m1;
		iPt.z = p1.z + (p2.z - p1.z)*m1;
		break;
	case Right:
		iPt.x = wMax.x;
		iPt.y = p1.y + (p2.y - p1.y)*m2;
		iPt.z = p1.z + (p2.z - p1.z)*m2;
		break;
	case Bottom:
		iPt.y = wMin.y;
		iPt.x = p1.x + (p2.x - p1.x)*m3;
		iPt.z = p1.z + (p2.z - p1.z)*m3;
		break;
	case Top:
		iPt.y = wMax.y;
		iPt.x = p1.x + (p2.x - p1.x)*m4;
		iPt.z = p1.z + (p2.z - p1.z)*m4;
		break;
	case Behind:
		iPt.z = wMin.z;
		iPt.x = p1.x + (p2.x - p1.x)*m5;
		iPt.y = p1.y + (p2.y - p1.y)*m5;
		break;
	case Front:
		iPt.z = wMax.z;
		iPt.x = p1.x + (p2.x - p1.x)*m6;
		iPt.y = p1.y + (p2.y - p1.y)*m6;
		break;
	}
	return iPt;
}

int edgeCliper(Boundary b, wcPt3D wMin, wcPt3D wMax, wcPt3D *pIn, int cnt, wcPt3D *pOut)
{
	wcPt3D s;
	int i, Outcnt = 0;
	s = pIn[0];
	for (i = 1; i <= cnt; i++)
	{
		if (!Inside(s, b, wMin, wMax) && Inside(pIn[i], b, wMin, wMax))
		{
			pOut[Outcnt] = Intersect(s, pIn[i], b, wMin, wMax);
			Outcnt++;
			pOut[Outcnt] = pIn[i];
			Outcnt++;
		}
		else if (Inside(s, b, wMin, wMax) && Inside(pIn[i], b, wMin, wMax))
		{
			pOut[Outcnt] = pIn[i];
			Outcnt++;

		}
		else if (Inside(s, b, wMin, wMax) && (!Inside(pIn[i], b, wMin, wMax)))
		{
			pOut[Outcnt] = Intersect(s, pIn[i], b, wMin, wMax);
			Outcnt++;
		}
		s = pIn[i];
	}
	return (Outcnt);
}

void  init(void)

{

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300.0, 300.0, -300.0, 300.0, -300.0, 300.0);
}

void ClipPolygonSuthHodgxy(void)    //在xy平面上投影函数 

{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	int i, cnt, Outcnt, b;
	wcPt3D points[4] = { { -100,-100,-100 },{ 0,200,0 },{ 200,0,0 },{ -100,-100,-100 } }; //被裁减三角形的三个顶点
	cnt = 3;
	wcPt3D pOut[28], pIn[28];
	wcPt3D wMin = { -50,-50,-50 }, wMax = { 50,50,50 };  //规范化观察体的边界 
	for (i = 0; i<4 * cnt; i++)
	{
		pIn[i].x = 0.0;
		pIn[i].y = 0.0;
		pIn[i].z = 0.0;
		pOut[i].x = 0.0;
		pOut[i].y = 0.0;
		pOut[i].z = 0.0;

	}

	for (i = 0; i <= cnt; i++) pIn[i] = points[i];
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(wMin.x, wMin.y, wMin.z);
	glVertex3f(wMax.x, wMin.y, wMin.z);
	glVertex3f(wMax.x, wMax.y, wMin.z);
	glVertex3f(wMin.x, wMax.y, wMin.z);
	glVertex3f(wMin.x, wMin.y, wMax.z);
	glVertex3f(wMax.x, wMin.y, wMax.z);
	glVertex3f(wMax.x, wMax.y, wMax.z);
	glVertex3f(wMin.x, wMax.y, wMax.z);
	glEnd();
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i<cnt; i++)
		glVertex2f(pIn[i].x, pIn[i].y);
	glEnd();

	for (b = 0; b<6; b++)
	{
		Outcnt = edgeCliper(Boundary(b), wMin, wMax, pIn, cnt, pOut);
		for (i = 0; i<Outcnt; i++)
			pIn[i] = pOut[i];
		pIn[Outcnt] = pOut[0];
		cnt = Outcnt;
	}
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i<cnt; i++)
		glVertex2f(pOut[i].x, pOut[i].y);
	glEnd();
	glFlush();

}

void ClipPolygonSuthHodgxz(void)    //在xz平面上投影函数 

{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	int i, cnt, Outcnt, b;
	wcPt3D points[4] = { { -100,-100,-100 },{ 0,200,0 },{ 200,0,0 },{ -100,-100,-100 } };//被裁减三角形的三个顶点 
	cnt = 3;
	wcPt3D pOut[28], pIn[28];
	wcPt3D wMin = { -50,-50,-50 }, wMax = { 50,50,50 };  //规范化观察体的边界
	for (i = 0; i<4 * cnt; i++)

	{
		pIn[i].x = 0.0;
		pIn[i].y = 0.0;
		pIn[i].z = 0.0;
		pOut[i].x = 0.0;
		pOut[i].y = 0.0;
		pOut[i].z = 0.0;
	}
	for (i = 0; i <= cnt; i++) pIn[i] = points[i];
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(wMin.x, wMin.y, wMin.z);
	glVertex3f(wMax.x, wMin.y, wMin.z);
	glVertex3f(wMax.x, wMax.y, wMin.z);
	glVertex3f(wMin.x, wMax.y, wMin.z);
	glVertex3f(wMin.x, wMin.y, wMax.z);
	glVertex3f(wMax.x, wMin.y, wMax.z);
	glVertex3f(wMax.x, wMax.y, wMax.z);
	glVertex3f(wMin.x, wMax.y, wMax.z);
	glEnd();
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i<cnt; i++)
		glVertex2f(pIn[i].x, pIn[i].z);
	glEnd();
	for (b = 0; b<6; b++)
	{
		Outcnt = edgeCliper(Boundary(b), wMin, wMax, pIn, cnt, pOut);
		for (i = 0; i<Outcnt; i++)
			pIn[i] = pOut[i];
		pIn[Outcnt] = pOut[0];
		cnt = Outcnt;

	}
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i<cnt; i++)
		glVertex2f(pOut[i].x, pOut[i].z);
	glEnd();
	glFlush();
}

void ClipPolygonSuthHodgyz(void)        //在yz平面上投影函数
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	int i, cnt, Outcnt, b;
	wcPt3D points[4] = { { -100,-100,-100 },{ 0,200,0 },{ 200,0,0 },{ -100,-100,-100 } }; //被裁减三角形的三个顶点
	cnt = 3;
	wcPt3D pOut[28], pIn[28];
	wcPt3D wMin = { -50,-50,-50 }, wMax = { 50,50,50 };  //规范化观察体的边界
	for (i = 0; i<4 * cnt; i++)
	{
		pIn[i].x = 0.0;
		pIn[i].y = 0.0;
		pIn[i].z = 0.0;
		pOut[i].x = 0.0;
		pOut[i].y = 0.0;
		pOut[i].z = 0.0;
	}
	for (i = 0; i <= cnt; i++) pIn[i] = points[i];
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(wMin.x, wMin.y, wMin.z);
	glVertex3f(wMax.x, wMin.y, wMin.z);
	glVertex3f(wMax.x, wMax.y, wMin.z);
	glVertex3f(wMin.x, wMax.y, wMin.z);
	glVertex3f(wMin.x, wMin.y, wMax.z);
	glVertex3f(wMax.x, wMin.y, wMax.z);
	glVertex3f(wMax.x, wMax.y, wMax.z);
	glVertex3f(wMin.x, wMax.y, wMax.z);
	glEnd();
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i<cnt; i++)
		glVertex2f(pIn[i].y, pIn[i].z);
	glEnd();
	for (b = 0; b<6; b++)
	{
		Outcnt = edgeCliper(Boundary(b), wMin, wMax, pIn, cnt, pOut);
		for (i = 0; i<Outcnt; i++)
			pIn[i] = pOut[i];
		pIn[Outcnt] = pOut[0];
		cnt = Outcnt;
	}
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i<cnt; i++)
		glVertex2f(pOut[i].y, pOut[i].z);
	glEnd();
	glFlush();
}

void main(int argc, char **argv)
{
	cout << "被裁减三角形三个顶点为(-100,-100,-100),(0,200,0),(200,0,0)" << endl;
	cout << " " << endl;
	cout << "规范化观察体为棱长=100的立方体，其八个顶点为(50,50,50),(-50,50,50)" << endl;
	cout << "(-50,-50,50),(50,-50,50),(50,50,-50),(-50,50,-50),(-50,-50,-50),(50,-50,-50)" << endl;
	cout << " " << endl;
	cout << "计算得裁剪后所剩三角形的三个顶点分别为：" << endl;
	cout << "(-50,50,-50),(50,-50,-50),(50,50,-25)" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("图案投影在xy平面上的图形");
	init();
	glutDisplayFunc(ClipPolygonSuthHodgxy);
	glutInitWindowPosition(80, 130);
	glutInitWindowSize(400, 400);
	glutCreateWindow("图案投影在xz平面上的图形");
	init();
	glutDisplayFunc(ClipPolygonSuthHodgxz);
	glutInitWindowPosition(110, 160);
	glutInitWindowSize(400, 400);
	glutCreateWindow("图案投影在yz平面上的图形");
	init();
	glutDisplayFunc(ClipPolygonSuthHodgyz);
	glutMainLoop();

}