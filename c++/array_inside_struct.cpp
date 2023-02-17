// implicit assignment operator copies array types
#include <iostream>
using namespace std;

struct S
{
    int arr[5];
};

int main(void) {
    S s1 = { { 5, 10, 100, 105, 110 } };
	S s2 = s1;
    
    cout << s2.arr[0] << ", " << s2.arr[1] << ", " << s2.arr[2] << ", " << s2.arr[3] << ", " << s2.arr[4] << endl;
}