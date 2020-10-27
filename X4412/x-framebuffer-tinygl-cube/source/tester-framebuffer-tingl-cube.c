#include <main.h>
#include <math.h>
#include <GL/gl.h>
static GLfloat Xrot, Xstep;
static GLfloat Yrot, Ystep;
static GLfloat Zrot, Zstep;
static GLfloat Step = 5.0;
static GLfloat Scale = 1.0;
static GLuint Object;

static GLuint make_object( void )
{
    GLuint list;

    list = glGenLists( 1 );

    glNewList( list, GL_COMPILE );

    glBegin( GL_LINE_LOOP );
    glColor3f( 1.0, 1.0, 1.0 );
    glVertex3f(  1.0,  0.5, -0.4 );
    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f(  1.0, -0.5, -0.4 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( -1.0, -0.5, -0.4 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -1.0,  0.5, -0.4 );
    glEnd();

    glColor3f( 1.0, 1.0, 1.0 );

    glBegin( GL_LINE_LOOP );
    glVertex3f(  1.0,  0.5, 0.4 );
    glVertex3f(  1.0, -0.5, 0.4 );
    glVertex3f( -1.0, -0.5, 0.4 );
    glVertex3f( -1.0,  0.5, 0.4 );
    glEnd();

    glBegin( GL_LINES );
    glVertex3f(  1.0,  0.5, -0.4 );   glVertex3f(  1.0,  0.5, 0.4 );
    glVertex3f(  1.0, -0.5, -0.4 );   glVertex3f(  1.0, -0.5, 0.4 );
    glVertex3f( -1.0, -0.5, -0.4 );   glVertex3f( -1.0, -0.5, 0.4 );
    glVertex3f( -1.0,  0.5, -0.4 );   glVertex3f( -1.0,  0.5, 0.4 );
    glEnd();


    glEndList();

    return list;
}

void reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 15.0 );
    glMatrixMode(GL_MODELVIEW);
}


void draw( void )
{
    glClear( GL_COLOR_BUFFER_BIT );

    glPushMatrix();

    glTranslatef( 0.0, 0.0, -10.0 );
    glScalef( Scale, Scale, Scale );
    if (Xstep) {
        glRotatef( Xrot, 1.0, 0.0, 0.0 );
    }
    else if (Ystep) {
        glRotatef( Yrot, 0.0, 1.0, 0.0 );
    }
    else {
        glRotatef( Zrot, 0.0, 0.0, 1.0 );
    }

    glCallList( Object );

    glPopMatrix();

    glFlush();
    vgafb_swap_buffer();
}

void idle( void )
{
    Xrot += Xstep;
    Yrot += Ystep;
    Zrot += Zstep;

    if (Xrot>=360.0) {
        Xrot = Xstep = 0.0;
        Ystep = Step;
    }
    else if (Yrot>=360.0) {
        Yrot = Ystep = 0.0;
        Zstep = Step;
    }
    else if (Zrot>=360.0) {
        Zrot = Zstep = 0.0;
        Xstep = Step;
    }
    draw();
}

void init(void)
{
    Object = make_object();
    glCullFace( GL_BACK );
    /*   glEnable( GL_CULL_FACE );*/
    glDisable( GL_DITHER );
    glShadeModel( GL_FLAT );
    /*   glEnable( GL_DEPTH_TEST ); */

    Xrot = Yrot = Zrot = 0.0;
    Xstep = Step;
    Ystep = Zstep = 0.0;
}

int tester_framebuffer_tingl_cube(int argc, char * argv[])
{
	struct vgafb_context *ctx = NULL;

	vgafb_create_context(&ctx);
	vgafb_make_current(ctx);

    init();
    reshape(1024, 600);
    while(1)
    {
    	idle();
    }
}
