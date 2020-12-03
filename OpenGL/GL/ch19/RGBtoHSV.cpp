class rgbSpace {public: float r, g, b;};
class hsvSpace {public: float h, s, v;};

const float noHue = -1.0;
inline float min(float a, float b) {return (a < b)? a : b;}
inline float max(float a, float b) {return (a > b)? a : b;}

void rgbTOhsv (rgbSpace& rgb, hsvSpace& hsv) 
{
   /* RGB and HSV values are in the range from 0 to 1.0 */ 
   float minRGB = min (r, min (g, b)), maxRGB = max (r, max (g, b));
   float deltaRGB = maxRGB - minRGB;

   v = maxRGB;
   if (maxRGB != 0.0)
      s = deltaRGB / maxRGB;
   else
      s = 0.0;
   if (s <= 0.0)
      h = noHue;
   else {
      if (r == maxRGB)
         h = (g - b) / deltaRGB;
      else 
         if (g == maxRGB)
            h = 2.0 + (b - r) / deltaRGB;
         else
            if (b == maxRGB)
               h = 4.0 + (r - g) / deltaRGB;
      h *= 60.0;
      if (h < 0.0)
         h += 360.0;
      h /= 360.0;
   }
}