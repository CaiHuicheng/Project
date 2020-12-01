#include <GL/glut.h>

GLsizei winWidth = 500, winHeight = 500;  // Initial display-window size.

void init (void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0);  // White display window.
}

void displayWirePolyhedra (void)
{
   glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.

   glColor3f (0.0, 0.0, 1.0);      // Set line color to blue.

   /*  Set viewing transformation.  */
   gluLookAt (5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   /*  Scale cube and display as wire-frame parallelepiped. */
   glScalef (1.5, 2.0, 1.0);
   glutWireCube (1.0);

   /*  Scale, translate, and display wire-frame dodecahedron. */
   glScalef (0.8, 0.5, 0.8);
   glTranslatef (-6.0, -5.0, 0.0);
   glutWireDodecahedron ( );

   /*  Translate and display wire-frame tetrahedron. */
   glTranslatef (8.6, 8.6, 2.0);
   glutWireTetrahedron ( );

   /*  Translate and display wire-frame octahedron. */
   glTranslatef (-3.0, -1.0, 0.0);
   glutWireOctahedron ( );

   /*  Scale, translate, and display wire-frame icosahedron. */
   glScalef (0.8, 0.8, 1.0);
   glTranslatef (4.3, -2.0, 0.5);
   glutWireIcosahedron ( );

   glFlush ( );
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
   glViewport (0, 0, newWidth, newHeight);

   glMatrixMode (GL_PROJECTION);
   glFrustum (-1.0, 1.0, -1.0, 1.0, 2.0, 20.0);

   glMatrixMode (GL_MODELVIEW);

   glClear (GL_COLOR_BUFFER_BIT);
}

void main (int argc, char** argv)
{
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition (100, 100);
   glutInitWindowSize (winWidth, winHeight);
   glutCreateWindow ("Wire-Frame Polyhedra");

   init ( );
   glutDisplayFunc (displayWirePolyhedra);
   glutReshapeFunc (winReshapeFcn);

   glutMainLoop ( );
}
