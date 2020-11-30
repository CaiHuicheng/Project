#include <cstdlib>
#include <cassert>
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
 
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glew32.lib")
 
using namespace std;
 
GLuint vertex_array[2] = {0,0};
 
void init()
{
	GLubyte indices[][4] ={
		{0,1,2,3},
		{4,7,6,5},
		{0,4,5,1},
		{3,2,6,7},
		{0,3,7,4},
		{1,5,6,2}
	};
 
	GLfloat vertexs[][3] = {
		{-1, -1, -1},
		{1, -1, -1},
		{1, 1, -1},
		{-1, 1, -1},
		{-1, -1, 1},
		{1, -1, 1},
		{1, 1, 1},
		{-1, 1, 1},
	};
 
	GLfloat color[][3] ={
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
		{0.5, 0, 0},
		{0, 0.5, 0},
		{0, 0, 0.5},
		{0.5, 0.5, 0.5},
		{0.8, 0.8, 0.8}
	};
 
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
 
	
	//VAO[0]
	glGenVertexArrays(2, vertex_array);
	
	glBindVertexArray(vertex_array[0]);
 
	//顶点数据
	GLuint vbo_vertex = 0;
	glGenBuffers(1, &vbo_vertex);
	assert(vbo_vertex != 0);
 
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*8, vertexs, GL_STATIC_DRAW);
	//Bind VAO and VBO 索引0一定是顶点
	//将顶点数据输入到VAO，用来建立VAO和VBO的数据传递，上传数据完成之后可以删除
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(0); //leave out this sentence
	
	//顶点颜色
	GLuint vbo_color = 0;
	glGenBuffers(1, &vbo_color);
	assert(vbo_color);
 
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*24, color, GL_STATIC_DRAW);
	glVertexAttribPointer(4,3,GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	//glColorPointer(3, GL_FLOAT, 0, 0);
	//glEnableClientState(GL_COLOR_ARRAY); //??????
 
	//assert(glGetError() == GLEW_OK);
	//使用VBO来实现顶点缓冲
	//GLuint vbo = 0;
	//glGenBuffers(1, &vbo);
	//assert(vbo != 0);
 
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*8, vertexs, GL_STATIC_DRAW);
	//glVertexPointer(3, GL_FLOAT, 0, 0);
	//glEnableClientState(GL_VERTEX_ARRAY);
 
	//将顶点索引写入显存
	GLuint vbo_index = 0;
	glGenBuffers(1, &vbo_index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*24, indices, GL_STATIC_DRAW);
 
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
 
	assert(glGetError() == GLEW_OK);
	
	//VAO[1]
	GLfloat vertex_triangle[][3] =
	{
		{0, 1, 0},
		{-1, -1, 0},
		{1, -1, 0}
	};
 
	GLfloat color_triangle [][3] =
	{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1}
	};
 
	GLubyte index_triangle[] = {0, 1, 2};
 
	glBindVertexArray(vertex_array[1]);
 
	GLuint vboID[3] = {0};
	glGenBuffers(3,vboID);
 
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, vertex_triangle, GL_STATIC_DRAW);
	//glVertexPointer(3, GL_FLOAT, 0, 0);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
 
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, color_triangle, GL_STATIC_DRAW);
	//glColorPointer(3, GL_FLOAT, 0, 0);
	//glEnableClientState(GL_COLOR_ARRAY);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*3, index_triangle, GL_STATIC_DRAW);
 
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
 
	assert(GLEW_OK == glGetError());
 
	GLint max_modelview_stack_count = 0;
	GLint max_projection_stack_count = 0;
	GLint max_clip_count = 0;
 
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &max_modelview_stack_count);
	glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &max_projection_stack_count);
	glGetIntegerv(GL_MAX_CLIP_PLANES, &max_clip_count);
 
	cout<<"max_modelview_stack_count="<<max_modelview_stack_count<<endl;
	cout<<"max_projection_stack_count"<<max_projection_stack_count<<endl;
	cout<<"max_clip_planes="<<max_clip_count<<endl;
}
 
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -10, 10);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
 
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glPushMatrix();
	{
		//glBindVertexArray(vertex_array[0]);
		//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, 0);
		//glBindVertexArray(0);
 
		//通过计算截取一个正方向// oh,yeah
		//GLdouble equ0[] = {1,0,0,0.5};
		//glClipPlane(GL_CLIP_PLANE0, equ0);
		//glEnable(GL_CLIP_PLANE0);
 
		//GLdouble equ1[] = {-1,0,0,0.5};
		//glClipPlane(GL_CLIP_PLANE1, equ1);
		//glEnable(GL_CLIP_PLANE1);
 
		//GLdouble equ2[] = {0,-1,0,0};
		//glClipPlane(GL_CLIP_PLANE2, equ2);
		//glEnable(GL_CLIP_PLANE2);
#if 1
		glBindVertexArray(vertex_array[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
#else
		glBindVertexArray(vertex_array[0]);
		glDrawArrays(GL_QUADS, 0, 24);
		glBindVertexArray(0);
#endif
 
		glDisable(GL_CLIP_PLANE0);
		glDisable(GL_CLIP_PLANE1);
		glDisable(GL_CLIP_PLANE2);
	}
	glPopMatrix();
 
	//Must call flush to update frame buffer
	glFlush();
}
 
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(500, 300);
	glutInitWindowSize(360, 360);
	glutCreateWindow("Vertex Array Object and Vertex Buffer Object");
 
	//创建窗口，建立上下文之后就可以调用glewInit()
	//glewInit()在使用glew的接口之前调用，否则会失败
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		cout<<"glewInit() failed!!!"<<endl;
		return EXIT_FAILURE;
	}
 
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
 
	glutMainLoop();
	return 0;
}