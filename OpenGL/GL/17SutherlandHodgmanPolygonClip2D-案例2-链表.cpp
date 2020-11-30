#include<iostream>
#include<gl\glut.h>
using namespace std;
int result[50][2] = { { 10, 80 },{ 70, 10 },{ 80, 80 },{ 90, 10 },{ 130, 80 },{ 80, 130 } };
enum mark { L, B, R, T };
int c = -1;
struct node {
	float data[2];
	node* next;
	node* pre;
};
void initNode(node *&head) {
	head = new node;
	head->data[0] = 0;
	head->data[1] = 0;
	head->next = NULL;
	head->pre = NULL;
	node *p = head;
	node *q = NULL;
	//此处直接输入的点的起始数目进行初始化
	for (int i = 0; i < 6; ++i) {
		q = new node;
		q->data[0] = result[i][0];
		q->data[1] = result[i][1];
		q->pre = p;
		p->next = q;
		p = q;
	}
	p->next = head;
	head->pre = p;
}
//分别对应每个边裁剪
void testPoint(node *&first, node *&head, int& edg, float xl, float xr, float yb, float yt) {
	if (edg == 4) {
		return;
	}
	node* p = first;
	node* q = p->pre;
	//依次对每个点处理，在线内的就存入result数组
	while (p != head) {
		int x = 0;
		int y = 0;
		if (q == head) {
			q = p->pre->pre;
		}
		float k = 0;
		if (q->data[0] - p->data[0] != 0) {
			k = (q->data[1] - p->data[1])*1.0 / (q->data[0] - p->data[0]);
		}
		switch (edg) {
		case L:
			//在边界之外的重新计算点
			if (((p->data[0] <= xl) && (q->data[0] >= xl)) || ((p->data[0] >= xl) && (q->data[0] <= xl))) {
				if ((q->data[0] >= xl) && (q->data[0] <= xr)) {
					c++;
					result[c][0] = q->data[0];
					result[c][1] = q->data[1];
				}
				//相连的点在边界内则计算新的交点
				x = xl;
				y = p->data[1] + (x - p->data[0]) * k;
				c++;
				result[c][0] = x;
				result[c][1] = y;
			}
			//处理的点再边界内,如果相连点也在边界内则把相连点插入
			else {
				c++;
				result[c][0] = q->data[0];
				result[c][1] = q->data[1];
			}
			break;
		case R:
			if (((p->data[0] >= xr) && (q->data[0] <= xr)) || ((p->data[0] <= xr) && (q->data[0] >= xr))) {
				if ((q->data[0] >= xl) && (q->data[0] <= xr)) {
					c++;
					result[c][0] = q->data[0];
					result[c][1] = q->data[1];
				}
				x = xr;
				y = p->data[1] + (x - p->data[0])*k;
				c++;
				result[c][0] = x;
				result[c][1] = y;
			}
			else {
				c++;
				result[c][0] = q->data[0];
				result[c][1] = q->data[1];
			}
			break;
		case B:
			if (((p->data[1] <= yb) && (q->data[1] >= yb)) || ((p->data[1] >= yb) && (q->data[1] <= yb))) {
				if ((q->data[1] >= yb) && (q->data[1] <= yt)) {
					c++;
					result[c][0] = q->data[0];
					result[c][1] = q->data[1];
				}
				if (k == 0) {    //处理两点垂直和平行情况
					if (p->data[1] != q->data[1]) {
						y = yb;
						x = p->data[0];
					}
					else {
						break;
					}
				}
				if (k != 0) {
					y = yb;
					x = p->data[0] + (y - p->data[1]) / k;
				}
				c++;
				result[c][0] = x;
				result[c][1] = y;
			}
			else {
				c++;
				result[c][0] = q->data[0];
				result[c][1] = q->data[1];
			}
			break;
		case T:
			if (((p->data[1] >= yt) && (q->data[1] <= yt)) || ((p->data[1] <= yt) && (q->data[1] >= yt))) {
				if ((q->data[1] >= yb) && (q->data[1] <= yt)) {
					c++;
					result[c][0] = q->data[0];
					result[c][1] = q->data[1];
				}
				if (k == 0) {
					if (p->data[1] != q->data[1]) {
						y = yb;
						x = p->data[0];
					}
					else {
						break;
					}
				}
				if (k != 0) {
					y = yt;
					x = p->data[0] + (y - p->data[1]) / k;
				}
				c++;
				result[c][0] = x;
				result[c][1] = y;
			}
			else {
				c++;
				result[c][0] = q->data[0];
				result[c][1] = q->data[1];
			}
			break;
		default:
			break;
		}
		//对处理点更新
		p = p->next;
		q = p->pre;
	}
	//对输入点进行更新
	p = head;
	node* qq = NULL;
	for (int i = 0; i <= c; ++i) {
		qq = new node;
		qq->data[0] = result[i][0];
		qq->data[1] = result[i][1];
		qq->pre = p;
		p->next = qq;
		p = qq;
	}
	p->next = head;
	head->pre = p;

	c = -1;
	edg++;
	p = p->next->next;
	testPoint(p, head, edg, xl, xr, yb, yt);
}
//对每个边进行裁剪
void getPoint(node* &head, float xl, float xr, float yb, float yt) {
	int n = 0;
	node* p = head->next;
	testPoint(p, head, n, xl, xr, yb, yt);
}
void drawPol() {
	//处理多边形顶点
	node *h = new node;
	initNode(h);
	//绘制原多边形
	node *p = h->next;
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	while (p != h) {
		glVertex2f(p->data[0], p->data[1]);
		p = p->next;
	}
	glEnd();
	//绘制
	getPoint(h, 20, 120, 20, 120);
	//绘制裁剪后的多边形
	p = h->next;
	glColor3f(1.0f, 1.0f, 0.0f);
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	while (p != h) {
		glVertex2f(p->data[0], p->data[1]);
		p = p->next;
	}
	glEnd();
}
void initPlo() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
	//绘制矩形线框
	glBegin(GL_LINE_LOOP);
	glVertex2f(20.f, 20.f);
	glVertex2f(20.f, 120.f);
	glVertex2f(120.f, 120.f);
	glVertex2f(120.f, 20.f);
	glEnd();
	drawPol();
	glFlush();
}
void changeSize(int w, int h) {
	if (h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(0.0f, 200.0f, 0.0f, 200.0f * h / w, 1.0f, -1.0f);
	}
	else {
		glOrtho(0.0f, 200.0f * w / h, 0.0f, 200.0f, 1.0f, -1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void setUpRc() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Plo");
	glutDisplayFunc(initPlo);
	glutReshapeFunc(changeSize);
	setUpRc();
	glutMainLoop();
}