glNewList (bicycle, GL_COMPILE);
   glCallList (frame);

   glPushMatrix ( );
     glTranslatef (tx1, ty1, tz1);
     glCallList (wheel);
   glPopMatrix ( );

   glPushMatrix ( );
     glTranslatef (tx2, ty2, tz2);
     glCallList (wheel);
   glPopMatrix ( );
glEndList ( );
