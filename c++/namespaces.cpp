// declaring without namespace { ... } is declaring inside global namespace

#include <iostream>
using namespace std;

class C { 
public:
    void printSmthg() const {
        cout << "hello" << endl;
    }
};

C c;        // defined in global namespace, can be used everywhere

namespace ns {
 
void f() {
    c.printSmthg();
}
    
}

namespace {

void f_anon() { cout << "anon namespace" << endl; }

}
// this is equivalent to using namespace *above*;
// all ids injected into global namespace

int main(void)
{
    ns::f();
    f_anon();
}