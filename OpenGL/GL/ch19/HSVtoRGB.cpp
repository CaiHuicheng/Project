class rgbSpace {public: float r, g, b;};
class hsvSpace {public: float h, s, v;};

void hsvT0rgb (hsvSpace& hsv, rgbSpace& rgb) 
{
   /*  HSV and RGB values are in the range from 0 to 1.0  */
   int k
   float aa, bb, cc, f;

   if ( s <= 0.0)
      r = g = b = v;       //  Have gray scale if s = 0.
   else {
      if (h == 1.0)
         h = 0.0;
      h *= 6.0;
      k = floor (h);
      f = h - k;
      aa = v * (1.0 - s);
      bb = v * (1.0 - (s * f));
      cc = v * (1.0 - (s * (1.0 - f)));
      switch (k)
      {
         case 0:  r = v;   g = cc;  b = aa; break;
         case 1:  r = bb;  g = v;   b = aa; break;
         case 2:  r = aa;  g = v;   b = cc; break;
         case 3:  r = aa;  g = bb;  b = v; break;
         case 4:  r = cc;  g = aa;  b = v; break;
         case 5:  r = v;   g = aa;  b = bb; break;
      }
   }
}
