GLubyte texArray [32][32][4];

/*  Next: assign the texture color components to texArray.  */

/*  Select nearest-color option.  */
glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, texArray);

glEnable (GL_TEXTURE_2D);

/*  Assign the full range of texture colors to a quadrilateral.  */
glBegin (GL_QUADS);
   glTexCoord2f (0.0, 0.0);     glVertex3fv (vertex1);
   glTexCoord2f (1.0, 0.0);     glVertex3fv (vertex2);
   glTexCoord2f (1.0, 1.0);     glVertex3fv (vertex3);
   glTexCoord2f (0.0, 1.0);     glVertex3fv (vertex4);
glEnd ( );

glDisable (GL_TEXTURE_2D);
