#include <iostream>
#include <memory>
using namespace std;

////////////definition inside class//////////////////
template<class T> class Templated {
    shared_ptr<T> data_p;
public:
    Templated(T* p) : data_p(p) { cout << "constructor | addr: " << this << endl; }
    virtual ~Templated() { cout << "destructor | addr: " << this << endl; }
    void func(const T* another_p) const { 
        cout << "addr: " << this << ", field: " << *data_p << ", argument: " << *another_p << endl;
    }
};
////////////definition inside class//////////////////

////////////definition outside class//////////////////
template<class T> class Templated2 {
    T* data_p;
public:
    Templated2(T* p);
    virtual ~Templated2();
    void func(const T* another_p) const;
};

template<class T> Templated2<T>::Templated2(T* p)
	: data_p(p) {
	cout << "constructor | addr: " << this << endl;
}

template<class T> Templated2<T>::~Templated2() {
	cout << "destructor | addr: " << this << endl;
}

template<class T> void Templated2<T>::func(const T* another_p) const {
	cout << "addr: " << this << ", field: " << *data_p << ", argument: " << *another_p << endl;
}
////////////definitin outside class//////////////////


int main(int argc, char* argv[]) {
	const int bad_num = 666;
	
    Templated<int> t(new int);
    t.func(&bad_num);
	
	Templated2<int> t2(new int);
	t2.func(&bad_num);
}