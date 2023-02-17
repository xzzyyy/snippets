// new and delete array syntax
#include <iostream>
using namespace std;

int main()
{
    int* arr = new int[3];
	
	// Type [cnt] is different type from Type* and will generate error when assigned this way
	int arr2[3];
	// arr2 = arr;     // error: incompatible types in assignment of 'int*' to 'int [3]'
	
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    
    cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << endl;
    
    delete[] arr;
}