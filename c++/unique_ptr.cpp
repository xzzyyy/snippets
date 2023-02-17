#include <iostream>
#include <memory>
using namespace std;


int main(int, char*[]) {
	int* p = new int(666);
	unique_ptr<int> unique_p1(p);
	// unique_ptr<int> unique_p2(p);        // warning: pointer used after 'void operator delete(void*)' [-Wuse-after-free]
	                                        // Error in `./a.out': double free or corruption
	cout << *unique_p1.get() /*<< ", " << *unique_p2.get()*/ << endl;
}
