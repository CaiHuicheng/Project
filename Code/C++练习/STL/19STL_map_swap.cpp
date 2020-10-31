 #include <map> 
 #include <iostream>
  using namespace std;
  int main( )
  {
      map < int, int > m1, m2, m3;
      map < int, int >::iterator m1_Iter;
      m1.insert ( pair < int, int >  ( 1, 10 ) );
      m1.insert ( pair < int, int >  ( 2, 20 ) );
      m1.insert ( pair < int, int >  ( 3, 30 ) );
      m2.insert ( pair < int, int >  ( 10, 100 ) );
      m2.insert ( pair < int, int >  ( 20, 200 ) );
      m3.insert ( pair < int, int >  ( 30, 300 ) );
   cout << "The original map m1 is:";
   for ( m1_Iter = m1.begin( ); m1_Iter != m1.end( ); m1_Iter++ )
      cout << " " << m1_Iter->second;
      cout   << "." << endl;
   // This is the member function version of swap
   //m2 is said to be the argument map; m1 the target map
   m1.swap( m2 );
   cout << "After swapping with m2, map m1 is:";
   for ( m1_Iter = m1.begin( ); m1_Iter != m1.end( ); m1_Iter++ )
      cout << " " << m1_Iter -> second;
      cout  << "." << endl;
   cout << "After swapping with m2, map m2 is:";
   for ( m1_Iter = m2.begin( ); m1_Iter != m2.end( ); m1_Iter++ )
      cout << " " << m1_Iter -> second;
      cout  << "." << endl;
   // This is the specialized template version of swap
   swap( m1, m3 );
   cout << "After swapping with m3, map m1 is:";
   for ( m1_Iter = m1.begin( ); m1_Iter != m1.end( ); m1_Iter++ )
      cout << " " << m1_Iter -> second;
      cout   << "." << endl;
}