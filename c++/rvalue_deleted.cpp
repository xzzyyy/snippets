#include <iostream>
#include <typeinfo>
using namespace std;


// template<class T> T& my_ref(T&&) = delete;
// template<class T> const T& my_ref(const T&&) = delete;       // I don't understand why this one is needed (probably it is not?)
                                                                // when we have template, version of T&& function with T = const Type will be created and deleted anyway
                                                                // so it is not needed in the context of template function, but will be useful in the context of explicit type to forbid using r-values as parameters

void process_ref(int& ref) {
    cout << "my_ref | type: " << typeid(ref).name() << ", val: " << ref << endl;
    ref += 1;
}
void process_ref(const int& ref) {       
    cout << "my_ref const | ref: " << ref << endl;
}
// void process_ref(int&&) = delete;        // redundant, r-value ref to modifiable resolves to r-value reference to const first
void process_ref(const int&&) = delete;


int main(int, char*[]) {
	int i = 666;
	const int x = 777;
	
	process_ref(i);
	process_ref(x);
	// process_ref(i + 1);      // temporary is modifiable r-value!
	                            // error: use of deleted function 'void process_ref(const int&&)'
	// process_ref(move(i));    // error: use of deleted function 'void process_ref(const int&&)'
	// process_ref(move(x));    // error: use of deleted function 'void process_ref(const int&&)'
}