class wcPt3D {
   public:
      GLfloat x, y, z;
};
typedef GLfloat Matrix4x4 [4][4];

Matrix4x4 matComposite;

/* Construct the 4 x 4 identity matrix. */
void matrix4x4SetIdentity (Matrix4x4 matIdent4x4)
{
   GLint row, col;

   for (row = 0; row < 4; row++)
      for (col = 0; col < 4 ; col++)
         matIdent4x4 [row][col] = (row == col);
}

/* Premultiply matrix m1 by matrix m2, store result in m2. */
void matrix4x4PreMultiply (Matrix4x4 m1, Matrix4x4 m2)
{
   GLint row, col;
   Matrix4x4 matTemp;

   for (row = 0; row < 4; row++)
      for (col = 0; col < 4 ; col++)
         matTemp [row][col] = m1 [row][0] * m2 [0][col] + m1 [row][1] *
                            m2 [1][col] + m1 [row][2] * m2 [2][col] +
                            m1 [row][3] * m2 [3][col];
   for (row = 0; row < 4; row++)
      for (col = 0; col < 4; col++)
         m2 [row][col] = matTemp [row][col];
}

/*  Procedure for generating 3D translation matrix.  */
void translate3D (GLfloat tx, GLfloat ty, GLfloat tz)
{
   Matrix4x4 matTransl3D;

   /*  Initialize translation matrix to identity.  */
   matrix4x4SetIdentity (matTransl3D);

   matTransl3D [0][3] = tx;
   matTransl3D [1][3] = ty;
   matTransl3D [2][3] = tz;

   /*  Concatenate matTransl3D with composite matrix.  */
   matrix4x4PreMultiply (matTransl3D, matComposite);
}

/*  Procedure for generating a quaternion rotation matrix.  */
void rotate3D (wcPt3D p1, wcPt3D p2, GLfloat radianAngle)
{
   Matrix4x4 matQuatRot;

   float axisVectLength = sqrt ((p2.x - p1.x) * (p2.x - p1.x) +
                        (p2.y - p1.y) * (p2.y - p1.y) +
                        (p2.z - p1.z) * (p2.z - p1.z));
   float cosA = cosf (radianAngle);
   float oneC = 1 - cosA;
   float sinA = sinf (radianAngle);
   float ux = (p2.x - p1.x) / axisVectLength;
   float uy = (p2.y - p1.y) / axisVectLength;
   float uz = (p2.z - p1.z) / axisVectLength;

   /*  Set up translation matrix for moving p1 to origin, 
    *  and concatenate translation matrix with matComposite.  
    */
   translate3D (-p1.x, -p1.y, -p1.z);

   /*  Initialize matQuatRot to identity matrix.  */
   matrix4x4SetIdentity (matQuatRot);

   matQuatRot [0][0] = ux*ux*oneC + cosA;
   matQuatRot [0][1] = ux*uy*oneC - uz*sinA;
   matQuatRot [0][2] = ux*uz*oneC + uy*sinA;
   matQuatRot [1][0] = uy*ux*oneC + uz*sinA;
   matQuatRot [1][1] = uy*uy*oneC + cosA;
   matQuatRot [1][2] = uy*uz*oneC - ux*sinA;
   matQuatRot [2][0] = uz*ux*oneC - uy*sinA;
   matQuatRot [2][1] = uz*uy*oneC + ux*sinA;
   matQuatRot [2][2] = uz*uz*oneC + cosA;

   /*  Concatenate matQuatRot with composite matrix.  */
   matrix4x4PreMultiply (matQuatRot, matComposite);

   /*  Construct inverse translation matrix for p1 and 
    *  concatenate with composite matrix.   
    */
   translate3D (p1.x, p1.y, p1.z);
}

/*  Procedure for generating a 3D scaling matrix.  */
void scale3D (Gfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt)
{
   Matrix4x4 matScale3D;

   /*  Initialize scaling matrix to identity.  */
   matrix4x4SetIdentity (matScale3D);

   matScale3D [0][0] = sx;
   matScale3D [0][3] = (1 - sx) * fixedPt.x;
   matScale3D [1][1] = sy;
   matScale3D [1][3] = (1 - sy) * fixedPt.y;
   matScale3D [2][2] = sz;
   matScale3D [2][3] = (1 - sz) * fixedPt.z;

   /*  Concatenate matScale3D with composite matrix.  */
   matrix4x4PreMultiply (matScale3D, matComposite);
}

void displayFcn (void)
{
   /*  Input object description.  */
   /*  Input translation, rotation, and scaling parameters.  */

   /* Set up 3D viewing-transformation routines. */

   /*  Initialize matComposite to identity matrix:  */
   matrix4x4SetIdentity (matComposite);

   /*  Invoke transformation routines in the order they
    *  are to be applied:  
    */
   rotate3D (p1, p2, radianAngle);  //  First transformation: Rotate.
   scale3D (sx, sy, sz, fixedPt);   //  Second transformation: Scale.
   translate3D (tx, ty, tz);        //  Final transformation: Translate.

   /*  Call routines for displaying transformed objects.  */
}
