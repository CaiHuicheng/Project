 #include <map> 
 #include <iostream>
 using namespace std;
 int main( )
 {
   map < int, int > m1;
   map < int, int >::iterator m1_Iter;
   m1.insert ( pair < int, int >  ( 1, 20 ) );
   m1.insert ( pair < int, int >  ( 4, 40 ) );
   m1.insert ( pair < int, int >  ( 3, 60 ) );
   m1.insert ( pair < int, int >  ( 2, 50 ) );
   m1.insert ( pair < int, int >  ( 6, 40 ) );
   m1.insert ( pair < int, int >  ( 7, 30 ) );
   cout << "The original map m1 is:"<<endl;
   for ( m1_Iter = m1.begin( ); m1_Iter != m1.end( ); m1_Iter++ )
      cout <<  m1_Iter->first<<" "<<m1_Iter->second<<endl;
}