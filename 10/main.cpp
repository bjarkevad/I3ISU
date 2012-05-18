#include <iostream>

#include "smartstring.h"
#include "csmartstring.h"

#include <boost/shared_ptr.hpp>



using namespace std;

int main(int argc, char* argv[])
{
   SmartString ss(new string("Hello World.."));
   cout << "String length: " << ss->length() << endl;

   if(ss->find("World") != string::npos)
     cout << "The 'ss' string does contain 'World'" << endl;
   else
     cout << "The 'ss' string does not contain 'World'" << endl;

   //NOTE: SmartString ss2 = ss; // The SmartString class is non-copyable, this will not compile, neither will using a copy constructor

   CSmartString css(new string("Hello Counted World.."));
   CSmartString css2(new string("Hello Counted World 2.."));

   cout << *css.get() << endl << *css2.get() << endl;

   {
   css2 = css;
   }

   //NOTE: Example shamelessly stolen from slide..

   boost::shared_ptr<string> bsp(new string("Hello shared_ptr"));
   boost::shared_ptr<string> bsp2;

   cout << bsp << "\t" << *bsp << "\t" << bsp.use_count() << endl;

   {
       boost::shared_ptr<string> bsp3(bsp);
       cout << bsp3 << "\t" << *bsp3 << "\t" << bsp3.use_count() << endl;

       bsp2 = bsp;
       cout << bsp2 << "\t" << *bsp2 << "\t" << bsp2.use_count() << endl;
   }

   bsp2.reset();
   cout << bsp << "\t" << *bsp << "\t" << bsp.use_count() << endl;

   bsp.reset();
   cout << bsp << "\t\t" << "xx" << "\t\t\t" << bsp.use_count() << endl;

}
