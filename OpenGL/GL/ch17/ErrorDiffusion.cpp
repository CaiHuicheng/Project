for (j = 0; j < m; j++)
   for (k = 0; k < n; k++) {
      /*  Determine the available system intensity value
       *  that is closest to the value of M [j][k] and
       *  assign this value to I [j][k].
       */
      error = M [j][k] - I [j][k];
      I [j][k+1]   = M [j][k+1]   + alpha * error;
      I [j+1][k-1] = M [j+1][k-1] + beta  * error;
      I [j+1][k]   = M [j+1][k]   + gamma * error;
      I [j+1][k+1] = M [j+1][k+1] + delta * error;
   }
