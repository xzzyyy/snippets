// operators inside class
#include <iostream>
using namespace std;

struct SuperInt
{
    int x;
    
	SuperInt(int x):
        x(x)
    {
    }
    
    SuperInt& operator+=(const SuperInt& superInt)
    {
        x += superInt.x;
        return *this;
    }
    
    SuperInt& operator*=(int r)
    {
        x *= r;
        return *this;
    }
};

int main()
{
    SuperInt superInt1(1), superInt2(2);
    
    superInt1 += superInt2;
    cout << superInt1.x << endl;
    
    superInt1 *= 3;
    cout << superInt1.x << endl;
}