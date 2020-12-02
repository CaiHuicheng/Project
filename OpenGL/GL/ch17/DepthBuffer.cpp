glEnable (GL_DEPTH_TEST);
/*  Process all opaque surfaces.  */

glEnable (GL_BLEND);
glDepthMask (GL_FALSE);
glBlendFunc (GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
/*  Process all transparent surfaces.  */

glDepthMask (GL_TRUE);
glDisable (GL_BLEND);

glutSwapBuffers ( );