class wcPt3D {
   public:
      GLfloat x, y, z;
};

/* Procedure for generating a matrix for rotation about
 * an axis defined with points p1 and p2.
 */
void rotate3D (wcPt3D p1, wcPt3D p2, GLfloat thetaDegrees)
{
   /*  Set up components for rotation-axis vector.  */
   float vx = (p2.x - p1.x);
   float vy = (p2.y - p1.y);
   float vz = (p2.z - p1.z);
   /* Specify translate-rotate-translate sequence in reverse order: */
   glTranslatef (p1.x, p1.y, p1.z); // Move p1 back to original position.
   /*  Rotate about axis through origin:  */
   glRotatef (thetaDegrees, vx, vy, vz); 
   glTranslatef (-p1.x, -p1.y, -p1.z);  // Translate p1 to origin.
}

/*  Procedure for generating a matrix for a scaling 
 *  transformation with respect to an arbitrary fixed point. 
 */
void scale3D (GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt)
{
   /* Specify translate-scale-translate sequence in reverse order: */
   /* (3) Translate fixed point back to original position: */
   glTranslatef (fixedPt.x, fixedPt.y, fixedPt.z);
   glScalef (sx, sy, sz);      // (2) Scale with respect to origin.
   /* (1) Translate fixed point to coordinate origin: */
   glTranslatef (-fixedPt.x, -fixedPt.y, -fixedPt.z);
}

void displayFcn (void)
{
   /*  Input object description.  */
   /*  Set up 3D viewing-transformation routines. */
   /*  Display object.  */
   glMatrixMode (GL_MODELVIEW);
   /* Input translation parameters tx, ty, tz. */
   /* Input the defining points, p1 and p2, for the rotation axis. */
   /* Input rotation angle in degrees. */
   /* Input scaling parameters: sx, sy, sz, and fixedPt. */
   /*  Invoke geometric transformations in reverse order:  */
   glTranslatef (tx, ty, tz);     // Final transformation: Translate.
   scale3D (sx, sy, sz, fixedPt);    // Second transformation: Scale.
   rotate3D (p1, p2, thetaDegrees);  // First transformation: Rotate.
   /*  Call routines for displaying transformed objects.  */
}
