#include <GL\glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.5f, 100.0, 100.0); //渲染一个球体 ，其半径为0.5
	glRotatef(90., 1.0, 0.0, 1.0);
	GLUquadricObj *quadObj; //创建一个二次曲面
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_SILHOUETTE);
	glShadeModel(GL_SMOOTH);
	glColor3f(0.0f, 1.0f, 0.0f);
	gluSphere(quadObj, 0.5f, 50.0f, 50.0f);
	glutSwapBuffers();//设立双缓冲
					  //二次曲面和实心球结合构成了一个网格求体

}
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 200.0f;
	//防止h为0，便于h为除数
	if (h == 0)
		h = 1;
	//设立视口到窗口之间的范围
	glViewport(0, 0, w, h);
	//重设投影矩阵
	glMatrixMode(GL_PROJECTION);//声明对投影矩阵进行操作
	glLoadIdentity();//更新
					 //正交投影变换
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_PROJECTION);//声明对模型视景矩阵进行操作
	glLoadIdentity();
}

void myInit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	//glShadeModel(GL_FLAT); 
	//glColor3f(1.0f,0.0f,0.0f);//以红色来绘制图形
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
	case 'X':
		glRotatef(100, 1.0, 0.0, 0.0);
		glutPostRedisplay();  //重绘窗口
		break;
	case 'y':
	case 'Y':
		glRotatef(100, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case 'z':
	case 'Z':
		glRotatef(100, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		glLoadIdentity();
		gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);//初始化
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);//设置窗口大小
	glutCreateWindow("球");//设置窗口名
	myInit();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}