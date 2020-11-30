#include<gl/glut.h>
#include <iostream>
using namespace std;

//定义一条线
//两个顶点(x1, y1)和(x2, y2)

struct Lines
{
	int x1;
	int y1;
	int x2;
	int y2;

};


//给出剪裁区域
int xleft = 200, xright = 400, ybuttom = 200, ytop = 400;


//虚拟出的直线，暂时有三条
Lines l1 = { 100,50,400,450 };
Lines l2 = { 200,100,400,300 };
Lines l3 = { 50,200,100,400 };

int cut_judge(float p, float q, float &u1, float &u2);

//画线
void LineGL(Lines &li) {
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(li.x1, li.y1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(li.x2, li.y2);
	glEnd();

}

//核心算法 更新线段的两端顶点
int LYD_Barskey(Lines &li) {
	int accept = 0;
	float u1 = 0.0, u2 = 1.0;
	float dx = li.x2 - li.x1, dy = li.y2 - li.y1;
	if (cut_judge(-dx, li.x1 - xleft, u1, u2)) {
		if (cut_judge(dx, xright - li.x1, u1, u2)) {
			if (cut_judge(-dy, li.y1 - ybuttom, u1, u2)) {
				if (cut_judge(dy, ytop - li.y1, u1, u2)) {
					if (u2 < 1.0) {
						li.x2 = li.x1 + u2 * dx;
						li.y2 = li.y1 + u2 * dy;

					}
					if (u1 > 0.0) {
						li.x1 = li.x1 + u1 * dx;
						li.y1 = li.y1 + u1 * dy;

					}
					accept = 1;
				}
			}
		}
	}

	if (accept) {
		LineGL(li);

	}
	else
	{
		li.x1 = 0;

		li.y1 = 0;

		li.x2 = 0;

		li.y2 = 0;

		LineGL(li);

	}
	return accept;
}

//更新u1和u2的值

int cut_judge(float p, float q, float &u1, float &u2) {
	float u;
	int res = 1;
	if (p > 0.0) {
		u = q / p;
		if (u < u1) {
			res = 0;

		}
		else if (u < u2)
		{
			u2 = u;
		}
	}

	else if (p < 0.0) {
		u = q / p;
		if (u > u2) {
			res = 0;
		}
		else if (u > u1) {
			u1 = u;
		}
	}

	else
	{
		if (q < 0.0) {
			res = 0;
		}
	}
	return res;

}





void Init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	//按下c键会进行剪裁，按下r键会复原，按下x键会退出窗口
	printf("Press key 'c' to Clip!\nPress key 'r' to Recover\nPress key 'x' to Exit\n");

}



void Reshape(int w, int h) {//窗口大小的改变函数
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);

}



void display() {//画图部分



	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(2);
	//画矩形 使用的是红色
	glBegin(GL_LINE_LOOP);
	glVertex2f(200, 200);
	glVertex2f(400, 200);
	glVertex2f(400, 400);
	glVertex2f(200, 400);
	glEnd();
	//画出最先开始的直线，没有经过任何修改
	LineGL(l1);
	LineGL(l2);
	LineGL(l3);
	glFlush();
}



//键盘监听事件

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'c':
		//按下c键以后，会进行裁剪工作
		LYD_Barskey(l1);
		LYD_Barskey(l2);
		LYD_Barskey(l3);
		glutPostRedisplay();//当前窗口重新绘制
		break;
	case 'r':
		//按下r键以后，原来的直线恢复，出现原本的线
		l1 = { 100,50,400,450 };
		l2 = { 200,100,400,300 };
		l3 = { 50,200,100,400 };
		Init();
		glutPostRedisplay();
		break;
	case 'x':
		exit(0);
		break;
	default:
		break;
	}
}





int main(int argc, char *argv[])

{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("梁友栋-Barskey裁剪算法");
	Init();
	glutDisplayFunc(&display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(&keyboard);//调用键盘监听事件
	glutMainLoop();
	return 0;
}