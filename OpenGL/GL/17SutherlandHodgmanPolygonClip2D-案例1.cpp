#include <gl\glut.h>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
float wid = 400;         //设置窗口的大小,约定窗口必须为正方形
float height = wid;      //设置窗口的大小
int numbers = 40;       //设置划分的网格的个数
float t = wid / numbers; //模拟像素下的单位1
int index_y;                 //记录下斜率为-1时的y的位置
int con[801][801];         //相当于我们的画布（其中的信息是有层次的）
int visited[801][801];
int flag = 0;                //标定移动轨迹的位置
int x_pos, y_pos, x_1 = 2 * wid, y_1 = 2 * wid;
int pixel_size = 8;       //统一设定所有的的pixel的大小；
						  /*
						  参数设置说明：
						  您应当确保参数范围在-400～400.且为整数。
						  由于使用的是模拟像素，应保持数据为单位模拟像素值的倍数。
						  */
int x = 0;
int y = 0;
int a = 300;
int b = 200;
void draw_point(float x, float y, float x1, float y1);
void add(int x, int y, int data) {
	con[x + 400][y + 400] = data;
}
float translater(int x) {
	/*
	函数说明：将像素坐标下的坐标转化为openGL坐标
	参数说明：传入点像素坐标-wid-wid，返回-1～1坐标
	*/
	return  x / wid;
}


void draw_point(float x, float y) {
	/*
	函数说明：绘制像素的点，这里将点的大小设置为7。
	颜色采用蓝色。利用圆八个部分的坐标对应关系进行绘图。
	加x1与y1是为了进行圆的平移
	参数说明：浮点数x，y是openGl坐标系。
	*/
	glPointSize(pixel_size);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0.0);
	glVertex3f(-x, y, 0.0);              //关于y轴对称
	glVertex3f(x, -y, 0.0);              //关于x轴对称
	glVertex3f(-x, -y, 0.0);            //关于原点对称
	glEnd();
	glFlush();
}
bool out_of_index(int x, int y) {
	if (y >= 801 || x >= 801 || x<0 || y<0) {
		return 0;
	}
	else {
		return 1;
	}
}

void draw_inner(int x, int y) {
	glPointSize(pixel_size);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3f(translater(x - 400), translater(y - 400), 0.0);
	glEnd();
	glFlush();
}
void draw_inner2(int x, int y) {
	glPointSize(pixel_size);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3f(translater(x - 400), translater(y - 400), 0.0);
	glEnd();
	glFlush();
}
void draw_line(int x, int y, int xx, int yy) {
	for (int i = min(x, xx); i <= max(x, xx); i += 10) {
		for (int j = min(y, yy); j <= max(y, yy); j += 10) {
			if (con[i][j] != 1) {
				int res = con[i][j] ^ 1111;
				if (res == -1) {
					glPointSize(pixel_size);
					glColor3f(1.0, 0.0, 0.0);
					glBegin(GL_POINTS);
					glVertex3f(translater(i - 400), translater(j - 400), 0.0);
					glEnd();
					glFlush();
				}
				else {
					draw_inner(i, j);
				}
				if (con[i][j] == 0) {
					con[i][j] = 1;
					visited[i][j] = 1;
				}
				else {
					con[i][j] = res;
				}
			}
		}
	}
}
void draw_line2(int x, int y, int xx, int yy) {
	for (int i = min(x, xx); i <= max(x, xx); i += 10) {
		for (int j = min(y, yy); j <= max(y, yy); j += 10) {
			if (con[i][j] != 1) {
				int res = con[i][j] ^ 1112;
				if (res == -1 && res == ((-1) ^ 1111)) {
					glPointSize(pixel_size);
					glColor3f(1.0, 0.0, 0.0);
					glBegin(GL_POINTS);
					glVertex3f(translater(i - 400), translater(j - 400), 0.0);
					glEnd();
					glFlush();
				}
				else {
					draw_inner2(i, j);
				}
				con[i][j] = res;
			}
		}
	}
}

void search(int x, int y, int index) {
	cout << index << " - - " << endl;
	/*
	函数说明：进行Dfs搜索并模拟四把刀当中的其中一把刀
	可视化着色采用淡蓝色。
	参数说明：x y是坐标，index是指明哪一把刀。
	传入的xy是数组坐标！
	*/
	if (visited[x][y] == 1) {
		return;
	}
	if (index == 1) {
		//讨论下方的情况
		if (flag == 0) {
			//如果本来在外侧
			if (y - 400 >= -200) {
				//从外侧进入内侧
				draw_inner(x, y);
				y_1 = min(y_1, y);
				x_1 = min(x_1, x);
				flag = 1;
				x_pos = x;
				y_pos = y;
			}
			else {
				glPointSize(pixel_size);
				glColor3f(0.5, 0.5, 0.5);
				glBegin(GL_POINTS);
				glVertex3f(translater(x - 400), translater(y - 400), 0.0);
				glEnd();
				glFlush();
				flag = 0;
				con[x][y] = 0;
			}
		}
		else if (flag == 1) {
			//如果本来在内侧进入了外侧
			if (y - 400 <= -200) {
				draw_inner(x, y);
				//从内侧进入外侧
				draw_line(x_pos, y_pos, x, y);
				x_pos = 0;
				y_pos = 0;
				flag = 0;
			}
			else {
				flag = 1;
				draw_inner(x, y);
				y_1 = min(y_1, y);
				x_1 = min(x_1, x);
			}
		}
		visited[x][y] = 1;
		if (out_of_index(x + 10, y) && con[x + 10][y] == 1 && visited[x + 10][y] == 0) {
			search(x + 10, y, index);
			visited[x + 10][y] = 1;
		}
		if (out_of_index(x, y + 10) && con[x][y + 10] == 1 && visited[x][y + 10] == 0) {
			search(x, y + 10, index);
			visited[x][y + 10] = 1;
		}
		if (out_of_index(x + 10, y + 10) && con[x + 10][y + 10] == 1 && visited[x + 10][y + 10] == 0) {
			search(x + 10, y + 10, index);
			visited[x + 10][y + 10] = 1;
		}
		if (out_of_index(x + 10, y - 10) && con[x + 10][y - 10] == 1 && visited[x + 10][y - 10] == 0) {
			search(x + 10, y - 10, index);
			visited[x + 10][y - 10] = 1;
		}
		if (out_of_index(x, y - 10) && con[x][y - 10] == 1 && visited[x][y - 10] == 0) {
			search(x, y - 10, index);
			visited[x][y - 10] = 1;
		}
		if (out_of_index(x - 10, y) && con[x - 10][y] == 1 && visited[x - 10][y] == 0) {
			search(x - 10, y, index);
			visited[x - 10][y] = 1;
		}
		if (out_of_index(x - 10, y + 10) && con[x - 10][y + 10] == 1 && visited[x - 10][y + 10] == 0) {
			search(x - 10, y + 10, index);
			visited[x - 10][y + 10] = 1;
		}
		if (out_of_index(x - 10, y - 10) && con[x - 10][y - 10] == 1 && visited[x - 10][y - 10] == 0) {
			search(x - 10, y - 10, index);
			visited[x - 10][y - 10] = 1;
		}
	}
	else if (index == 2) {
		//讨论左侧的情况
		if (flag == 0) {
			//如果本来在外侧
			if (x - 400 >= -300) {
				draw_inner2(x, y);
				//从外侧进入内侧
				flag = 1;
				x_pos = x;
				y_pos = y;
			}
			else {
				glPointSize(pixel_size);
				glColor3f(1.0, 1.0, 1.0);
				glBegin(GL_POINTS);
				glVertex3f(translater(x - 400), translater(y - 400), 0.0);
				glEnd();
				glFlush();
				flag = 0;
			}
		}
		else if (flag == 1) {
			//如果本来在内侧进入了外侧
			if (x - 400 <= -300) {
				draw_inner2(x, y);
				//从内侧进入外侧
				cout << "inner -> outer  " << endl;
				cout << x_pos << " == " << y_pos << endl;
				cout << x << " === " << y << endl;
				draw_line2(x_pos, y_pos, x, y);
				cout << con[x - 10][y] << "here !!  " << endl;
				x_pos = 0;
				y_pos = 0;
				flag = 0;
			}
			else {
				flag = 1;
				draw_inner2(x, y);
			}
		}
		visited[x][y] = 1;
		if (out_of_index(x + 10, y) && (con[x + 10][y] == 1 || con[x + 10][y] == (-1 ^ 1111)) && visited[x + 10][y] == 0) {
			search(x + 10, y, index);
			visited[x + 10][y] = 1;
		}
		if (out_of_index(x, y + 10) && (con[x][y + 10] == 1 || con[x][y + 10] == (-1 ^ 1111)) && visited[x][y + 10] == 0) {
			search(x, y + 10, index);
			visited[x][y + 10] = 1;
		}
		if (out_of_index(x + 10, y + 10) && (con[x + 10][y + 10] == 1 || con[x + 10][y + 10] == (-1 ^ 1111)) && visited[x + 10][y + 10] == 0) {
			search(x + 10, y + 10, index);
			visited[x + 10][y + 10] = 1;
		}
		if (out_of_index(x + 10, y - 10) && (con[x + 10][y - 10] == 1 || con[x + 10][y - 10] == (-1 ^ 1111)) && visited[x + 10][y - 10] == 0) {
			search(x + 10, y - 10, index);
			visited[x + 10][y - 10] = 1;
		}
		if (out_of_index(x, y - 10) && (con[x][y - 10] == 1 || con[x][y - 10] == (-1 ^ 1111)) && visited[x][y - 10] == 0) {
			search(x, y - 10, index);
			visited[x][y - 10] = 1;
		}
		if (out_of_index(x - 10, y) && (con[x - 10][y] == 1 || con[x - 10][y] == (-1 ^ 1111)) && visited[x - 10][y] == 0) {
			search(x - 10, y, index);
			visited[x - 10][y] = 1;
		}
		if (out_of_index(x - 10, y + 10) && (con[x - 10][y + 10] == 1 || con[x - 10][y + 10] == (-1 ^ 1111)) && visited[x - 10][y + 10] == 0) {
			search(x - 10, y + 10, index);
			visited[x - 10][y + 10] = 1;
		}
		if (out_of_index(x - 10, y - 10) && (con[x - 10][y - 10] == 1 || con[x - 10][y - 10] == (-1 ^ 1111)) && visited[x - 10][y - 10] == 0) {
			search(x - 10, y - 10, index);
			visited[x - 10][y - 10] = 1;
		}
	}

}
void cutter(int x, int y) {
	/*
	函数说明：这里包含四把刀
	参数说明：传入我们的起始坐标
	*/
	//首先判断点的位置：框内？框外？
	for (int i = 0; i <801; i++) {
		for (int j = 0; j < 801; j++) {
			visited[i][j] = 0;
		}
	}
	if (y < -200) {
		//在下方
		flag = 0;            //在下方外侧
		search(x + 400, y + 400, 1);

	}
	if (x < -300) {
		//在左侧！
		flag = 0;
		for (int i = 0; i <801; i++) {
			for (int j = 0; j < 801; j++) {
				visited[i][j] = 0;
			}
		}
		glPointSize(pixel_size);
		glColor3f(0.9, 0.89, 0.1);
		glBegin(GL_POINTS);
		glVertex3f(translater(x_1 - 400), translater(y_1 - 400), 0.0);
		glEnd();
		glFlush();
		cout << "xx " << x_1 - 400 << "  " << y_1 - 400 << endl;
		search(x_1, y_1, 2);
	}


}
void p(float x, float y, float x1, float y1) {
	/*
	函数说明：绘制像素的点，这里将点的大小设置为7。
	颜色采用蓝色。利用圆八个部分的坐标对应关系进行绘图。
	加x1与y1是为了进行圆的平移
	参数说明：浮点数x，y是openGl坐标系。
	*/
	glPointSize(pixel_size);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(x + x1, y + y1, 0.0);
	glEnd();
	glFlush();
}
void paint(int x, int y) {
	add(x, y, 1);
	p(translater(x), translater(y), 0, 0);
}
void grid() {
	/*
	函数说明：绘制网格为了便于将真实的像素pixel转化为我们模拟的像素
	*/
	glClearColor(0, 0, 0, 0);//这是设置背景色,必须要在glclear之前调用
	glClear(GL_COLOR_BUFFER_BIT);
	int hei_number = numbers;
	float delta_hei = height / hei_number;
	glColor3f(0.0, 1.0, 0);
	for (int i = 1; i < numbers * 2; i++) { //利用循环绘制网格
		glBegin(GL_LINES);
		glVertex2f(-1 + i*delta_hei / height, -1);
		glVertex2f(-1 + i*delta_hei / height, 1);
		glVertex2f(-1, -1 + i*delta_hei / height);
		glVertex2f(1, -1 + i*delta_hei / height);
		glEnd();
		glFlush();
	}
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINES);          //绘制坐标系，便于观察
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(0, -1);
	glVertex2f(0, 1);
	glEnd();
	glFlush();
	//绘制我们的框图
	for (int i = 0; i <= 300; i += t) {
		draw_point(translater(i), translater(200));
		add(i, 200, -1);
		add(-i, 200, -1);
		add(i, -200, -1);
		add(-i, -200, -1);

	}
	for (int i = 0; i <= 200; i += t) {
		draw_point(translater(300), translater(i));
		add(300, i, -1);
		add(-300, i, -1);
		add(300, -i, -1);
		add(-300, -i, -1);
	}
	//绘制多边形
	int dm = -370;
	//设置偏移量
	for (int i = 140; i <= 240; i += 10) {
		paint(i, i + dm);
	}
	for (int i = 240; i <= 340; i += 10) {
		paint(240, i + dm);
		//绘制横线
	}
	for (int i = 240; i >= -200; i -= 10) {
		paint(i, 340 + dm);
	}
	for (int i = -200; i >= -380; i -= 10) {
		paint(i, 540 + i + dm);
	}
	for (int i = -200; i >= -380; i -= 10) {
		paint(i, 540 + i + dm);
	}
	for (int i = 160; i >= -20; i -= 10) {
		paint(-380, i + dm);
	}
	for (int i = 1; i <= 30; i++) {
		paint(-380 + i * 10, -20 + i * 10 + dm);
	}
	for (int i = 1; i <= 14; i++) {
		paint(-80 + i * 10, 280 - i * 10 + dm);
	}
	for (int i = 60; i <= 140; i += 10) {
		paint(i, 140 + dm);
	}
	cutter(-380, -390);
	//刷新缓冲，保证绘图命令能被执行
}



int main(int argc, char *argv[]) {
	//初始化GLUT library
	glutInit(&argc, argv);
	//对窗口的大小进行初始化
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(300, 200);
	// 设置窗口出现的位置
	//glutInitWindowPosition(int x, int y);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("hw_多边形裁剪");
	glutDisplayFunc(&grid);
	glutMainLoop();
	return 0;
}