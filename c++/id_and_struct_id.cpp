#include <iostream>
using namespace std;

struct MyTimeval
{
	long tv_sec;
	long tv_usec;
};

long MyTimeval = 0;

int main(int argc, char* argv[])
{
	struct MyTimeval tv;			// C++ language -> Declarations -> Specifiers -> Elaborated type specifier
	++MyTimeval;
	
    tv.tv_sec = 1;
    tv.tv_usec = 2;
    
	cout << tv.tv_sec << endl;
	cout << tv.tv_usec << endl;
	cout << MyTimeval << endl;
}