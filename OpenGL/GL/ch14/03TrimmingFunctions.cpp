GLUnurbsObj *bezSurface;

GLfloat outerTrimPts [5][2] = { {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0),
                                  {0.0, 1.0}, {0.0, 0.0} };
GLfloat innerTrimPts1 [3][2] = { {0.25, 0.5}, {0.5, 0.75},
                                  {0.75, 0.5) };
GLfloat innerTrimPts2 [4][2] = { {0.75, 0.5}, {0.75, 0.25},
                                  {0.25, 0.25), {0.25, 0.5} };

GLfloat surfKnots [8] = (0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
GLfloat trimCurveKnots [8] = (0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);

bezSurface = gluNewNurbsRenderer ( );

gluBeginSurface (bezSurface);
   gluNurbsSurface (bezSurface, 8, surfKnots, 8, surfKnots, 4 * 3, 3,
                      &ctrlPts [0][0][0], 4, 4, GL_MAP2_VERTEX_3);
   gluBeginTrim (bezSurface);
       /*  Counterclockwise outer trim curve.  */
   gluPwlCurve (bezSurface, 5, &outerTrimPts [0][0], 2, GLU_MAP1_TRIM_2);
   gluEndTrim (bezSurface);
   gluBeginTrim (bezSurface);
       /*  Clockwise inner trim-curve sections.  */
   gluPwlCurve (bezSurface, 3, &innerTrimPts1 [0][0], 2, GLU_MAP1_TRIM_2);
   gluNurbsCurve (bezSurface, 8, trimCurveKnots, 2, 
                    &innerTrimPts2 [0][0], 4, GLU_MAP1_TRIM_2):
   gluEndTrim (bezSurface);
gluEndSurface (bezSurface);