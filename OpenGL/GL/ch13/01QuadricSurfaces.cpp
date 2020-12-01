#include <GL/glut.h>

GLsizei winWidth = 500, winHeight = 500;    

void init (void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0);       
}

void wireQuadSurfs (void)
{
   glClear (GL_COLOR_BUFFER_BIT);           

   glColor3f (0.0, 0.0, 1.0);               


   /*  将世界 z 轴的查看参数设置为向上查看方向  */
   gluLookAt (2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

   /* 位置和显示 GLUT 线框球体  */
   glPushMatrix ( );
   glTranslatef (1.0, 1.0, 0.0);
   glutWireSphere (0.75, 8, 6);
   glPopMatrix ( );

   /*  放置和显示 GLUT 线框圆锥体  */
   glPushMatrix ( );
   glTranslatef (1.0, -0.5, 0.5);
   glutWireCone (0.7, 2.0, 7, 6);
   glPopMatrix ( );

   /*  放置并显示 GLU 线框气缸  */
   GLUquadricObj *cylinder;   // 为 GLU 四位对象设置名称。.
   glPushMatrix ( );
   glTranslatef (0.0, 1.2, 0.8);
   cylinder = gluNewQuadric ( );
   gluQuadricDrawStyle (cylinder, GLU_LINE);
   gluCylinder (cylinder, 0.6, 0.6, 1.5, 6, 4);
   glPopMatrix ( );

   glFlush ( );
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
   glViewport (0, 0, newWidth, newHeight);

   glMatrixMode (GL_PROJECTION);
   glOrtho (-2.0, 2.0, -2.0, 2.0, 0.0, 5.0);

   glMatrixMode (GL_MODELVIEW);

   glClear (GL_COLOR_BUFFER_BIT);
}

void main (int argc, char** argv)
{
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition (100, 100);
   glutInitWindowSize (winWidth, winHeight);
   glutCreateWindow ("Wire-Frame Quadric Surfaces");

   init ( );
   glutDisplayFunc (wireQuadSurfs);
   glutReshapeFunc (winReshapeFcn);

   glutMainLoop ( );
}
