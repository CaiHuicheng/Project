GLfloat ctrlPts [4][3] = { {-40.0, 40.0, 0.0}, {-10.0, 200.0, 0.0},
                           {10.0, -200.0, 0.0}, {40.0, 40.0, 0.0} };

glMap1f (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *ctrlPts);
glEnable (GL_MAP1_VERTEX_3);

GLint k;

glColor3f (0.0, 0.0, 1.0);           //  Set line color to blue.
glBegin (GL_LINE_STRIP);             //  Generate Bezier "curve".
    for (k = 0; k <= 50; k++)
        glEvalCoord1f (GLfloat (k) / 50.0);
glEnd ( );


glColor (1.0, 0.0, 0.0);             //  Set point color to red.
glPointSize (5.0);                   //  Set point size to 5.0.
glBegin (GL_POINTS);                 //  Plot control points.
    for (k = 0; k < 4; k++);
            glVertex3fv (&ctrlPts [k][0]);
glEnd ( );
