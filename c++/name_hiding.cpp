// function doesn't resolve to parent class if there is overload in child class

#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;


struct A {
    void print() const { cout << "class A" << endl; }
    void gopa() const { cout << "gopa is not overloaded" << endl; }
};

struct B : A {
    void print(int num) const { cout << "class C: " << num << endl; }
};


int main() {
    boost::shared_ptr<B> b_p(new B);
    // b_p->print();                       // error: no matching function for call to 'B::print()'
    b_p->A::print();
    b_p->print(666);
    b_p->gopa();
}
