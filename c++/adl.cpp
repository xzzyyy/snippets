#include <iostream>
using namespace std;

template <class T> 
struct S
{
    S(T* arg)
    {
        f(arg);
    }
};

struct MyClass
{
    MyClass()
    {
        cout << "MyClass created | &: " << this << endl;
    }
    
    ~MyClass()
    {
        cout << "MyClass destroyed | &: " << this << endl;
    }
};

void f(int* arg)
{
    cout << "f func: " << arg << endl;
}

void f(MyClass* arg)
{
    cout << "f func: " << arg << endl;
}

int main(int argc, char* argv[])
{
    S<MyClass> inst(new MyClass);		// works, ADL
    // S<int> inst_int(new int);	    // doesn't work, non-ADL
}