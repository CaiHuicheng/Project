GLint k;
GLubyte texLine [16];   // 16-element texture array.

/*  Define two green elements for the texture pattern.  
/*  Each texture color is specified in four array positions.  
 */
for (k = 0; k <= 2; k += 2)
{
   texLine [4*k]   = 0;
   texLine [4*k+1] = 255;
   texLine [4*k+2] = 0;
   texLine [4*k+3] = 255;
}

/*  Define two red elements for the texture pattern.  */
for (k = 1; k <= 3; k += 2)
{
   texLine [4*k]   = 255;
   texLine [4*k+1] = 0;
   texLine [4*k+2] = 0;
   texLine [4*k+3] = 255;
}

glTexParameteri (GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri (GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

glTexImage1D (GL_TEXTURE_1D, 0, GL_RGBA, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, texLine);

glEnable (GL_TEXTURE_1D);

/*  Assign the full range of texture colors to a line segment.  */
glBegin (GL_LINES);
   glTexCoord1f (0.0);
   glVertex3fv (endPt1);
   glTexCoord1f (1.0);
   glVertex3fv (endPt2);
glEnd ( );

glDisable (GL_TEXTURE_1D);