#include <GL/glut.h>
#include <iostream>

/* -- - 常量-- - */
const int HEIGHT(800);
const int WIDTH(800);

void Display();
void Reshape(int w, int h);
void init();

int time(0);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//glut初始化

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//双缓存模式

	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(50, 100);
	//窗口初始化

	glClearColor(0, 0, 0, 1);
	//窗口颜色

	glutCreateWindow("Window - 3D");
	//窗口

	init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	return 0;
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidSphere(1.0, 300, 16);//半径，南北经线，纬线

								  //双缓存使用glutSwapBuffers，但缓存glFlush
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//使像素矩阵占据整个新窗口
	glMatrixMode(GL_PROJECTION);//设置当前矩阵为投影矩阵
	glLoadIdentity();

	float nowRange = 1.5;
	GLfloat nRange = (GLfloat)nowRange;

	if (w <= h) //改变窗口大小，图形形状不变
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);//模型矩阵,告诉我们当前矩阵
	glLoadIdentity();
}

void init()
{
	//光源light0
	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_shininess[] = { 128.0 };

	GLfloat light_position[] = { 1.0,1.0,1.0,0.0 };//1.0表示光源为点坐标x,y,z
	GLfloat white_light[] = { 1.0,1.0,1.0,1.0 };   //光源的颜色
	GLfloat lmodel_ambient[] = { 0.2,0.2,0.2,1.0 };//微弱环境光，使物体可见
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);//GL_SMOOTH

							//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//指定当前材质属性 镜面反射颜色
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); //镜面反射指数

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//光源编号-7，光源特性，参数数据
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //指定全局的环境光，物体才能可见//*/

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}