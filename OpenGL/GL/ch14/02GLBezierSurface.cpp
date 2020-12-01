GLfloat ctrlPts [4][4][3] = {
   { {-1.5, -1.5,  4.0}, {-0.5, -1.5,  2.0},
     {-0.5, -1.5, -1.0}, { 1.5, -1.5,  2.0} },
   { {-1.5, -0.5,  1.0}, {-0.5, -0.5,  3.0},
     { 0.5, -0.5,  0.0}, { 1.5, -0.5, -1.0} },
   { {-1.5,  0.5,  4.0}, {-0.5,  0.5,  0.0},
     { 0.5,  0.5,  3.0}, { 1.5,  0.5,  4.0} },
   { {-1.5,  1.5, -2.0}, {-0.5,  1.5, -2.0},
     { 0.5,  1.5,  0.0}, { 1.5,  1.5, -1.0} }
};

glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4,
              0.0, 1.0, 12, 4, &ctrlPts[0][0][0]);
glEnable (GL_MAP2_VERTEX_3);

GLint k, j;

glColor3f (0.0, 0.0, 1.0);
for (k = 0; k <= 8; k++)
{
    glBegin (GL_LINE_STRIP);  // Generate Bezier surface lines.
    for (j = 0; j <= 40; j++)
        glEvalCoord2f (GLfloat (j) / 40.0, GLfloat (k) / 8.0);
    glEnd ( );
    glBegin (GL_LINE_STRIP);
    for (j = 0; j <= 40; j++)
        glEvalCoord2f (GLfloat (k) / 8.0, GLfloat (j) / 40.0);
    glEnd ( );
}
