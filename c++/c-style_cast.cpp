#include <iostream>
using namespace std;

struct A {
    int f;
};

struct B {
    unsigned f;
};

int main() {
    A a = { 1 };
    B b = { 2 };

    A* ap = &a;
    B* bp = &b;

    // ap = static_cast<A*>(bp);                // error: invalid ‘static_cast’ from type ‘B*’ to type ‘A*’
    ap = (A*)bp;

    cout << "inside ap: " << ap->f << endl;     // inside ap: 2
}
