#include "./vector.h"
#include <vector>
#include <iostream>

//We do NOT want to include either statement. We wouldn't
//be able to compare our vector template to the Standard
//using namespace std;
//using std::vector;
using std::cout;
using std::endl;

int main (){
   vector<int> v;   //Our vector class
   std::vector<int> stdv; //Standard vector from <vector>

   //Compare operation of our vector to std
   v.push_back(23);
   stdv.push_back(23);

   //both of the following should display "1"
   cout << "Our vector size: " << v.size() << endl;
   cout << "STL vector size: " << stdv.size() << endl;


   //Step 1.....
   //uncomment the following to test Copy Construtor
    vector<int> v2 = v; //envoke cc
    cout << "v2 size: " << v2.size() << endl; //should display 1

   //uncomment the following to test AOO
    vector<int> v3;
    v3.push_back(10);
    v3.push_back(100);
    v3.push_back(1000);
    cout << "v3 size: " << v3.size() << endl; //should display 3
    v3 = v; //envoke aoo
    cout << "v3 size: " << v3.size() << endl; //should display 1


   //Step 2...
    cout << "v[0]: " << v[0] << endl; //should display 23
    cout << "stdv[0]: " << stdv[0] << endl; //should display 23

    v3.push_back(500);
    cout << "v3[1]: " << v3[1] << endl; //should display 500
    cout << "v[1]: " << v[1] << endl; //should display a garbage or crash the program

   //should throw an "out_of_range" exception
   //and exit the program gracefully
  try { cout << "v.at(1): " << v.at(1) << endl;
} catch (const std::out_of_range &e) {
    cout << "Caught exception: " << e.what() << endl;
}

   //Step 3...
   //Include your own testing code to prove that
   //your push_back(), resize(), and reserve() works


   return 0;
}
