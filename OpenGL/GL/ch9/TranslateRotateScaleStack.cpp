glMatrixMode (GL_MODELVIEW);

glColor3f (0.0, 0.0, 1.0);         // Set current color to blue. 
glRecti (50, 100, 200, 150);       // Display blue rectangle. 

glPushMatrix ( );                  // Make copy of identity (top) matrix. 
glColor3f (1.0, 0.0, 0.0);         // Set current color to red. 

glTranslatef (-200.0, -50.0, 0.0); // Set translation parameters. 
glRecti (50, 100, 200, 150);       // Display red, translated rectangle. 

glPopMatrix ( );                   // Throw away the translation matrix. 
glPushMatrix ( );                  // Make copy of identity (top) matrix. 

glRotatef (90.0, 0.0, 0.0, 1.0);   // Set 90-deg. rotation about z axis. 
glRecti (50, 100, 200, 150);       // Display red, rotated rectangle. 

glPopMatrix ( );                   // Throw away the rotation matrix. 
glScalef (-0.5, 1.0, 1.0);         // Set scale-reflection parameters. 
glRecti (50, 100, 200, 150);       // Display red, transformed rectangle. 
