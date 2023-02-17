#include <iostream>
#include <unordered_map>
#include <boost/smart_ptr/intrusive_ptr.hpp>
using namespace std;


unordered_map<void*, int> smart_ptr_cnt;

template<class T>
void intrusive_ptr_add_ref(T* p)
{
	++smart_ptr_cnt[p];
	cout << "ref counter " << p << " incremented" << endl;
}
 
template<class T>
void intrusive_ptr_release(T* p)
{
    cout << "ref counter " << p << " decremented" << endl;
	if (--smart_ptr_cnt[p] == 0)
	{
	    cout << "deleting " << p << endl;
		delete p;
	}
}

class MyClass {};

void func(boost::intrusive_ptr<MyClass> ip)
{
    cout << "inside func | pointer: " << ip.get() << endl;
}


int main(int argc, char* argv[])
{
    boost::intrusive_ptr<MyClass> mc(new MyClass);
    func(mc);
}


// ref counter 0x108cc20 incremented
// ref counter 0x108cc20 incremented
// inside func | pointer: 0x108cc20
// ref counter 0x108cc20 decremented
// ref counter 0x108cc20 decremented
// deleting 0x108cc20