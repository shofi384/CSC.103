/*
 * CSc103 Project 1: (hello_world++)
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:Programming principles and practice using c++
 *Data Structures and other objects using C++
 *
 */
#include <iostream>
using namespace std;

int main()
{
 string name, relative;
 cout<<"Enter your name:\n";
 cin >> name;
 cout << "Enter a relative:\n";
 cin >> relative;
 cout <<"Hello. My name is " << name <<". You killed my " << relative <<". Prepare to die."<<endl;
}
