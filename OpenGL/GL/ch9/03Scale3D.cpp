class wcPt3D 
{
   private:
      GLfloat x, y, z;

   public:
   /*  Default Constructor:
    *  Initialize position as (0.0, 0.0, 0.0).
    */
   wcPt3D ( ) {
      x = y = z = 0.0;
   }

   setCoords (GLfloat xCoord, GLfloat yCoord, GLfloat zCoord) {
      x = xCoord;
      y = yCoord;
      z = zCoord;
   }

   GLfloat getx ( ) const {
      return x;
   }

   GLfloat gety ( ) const {
      return y;
   }

   GLfloat getz ( ) const {
      return z;
   }
};

typedef float Matrix4x4 [4][4];

void scale3D (GLfloat sx, GLfloat sy, GLfloat sz, wcPt3D fixedPt)
{
   Matrix4x4 matScale3D;

   /*  Initialize scaling matrix to identity.  */
   matrix4x4SetIdentity (matScale3D);

   matScale3D [0][0] = sx;
   matScale3D [0][3] = (1 - sx) * fixedPt.getx ( );
   matScale3D [1][1] = sy;
   matScale3D [1][3] = (1 - sy) * fixedPt.gety ( );
   matScale3D [2][2] = sz;
   matScale3D [2][3] = (1 - sz) * fixedPt.getz ( );
}