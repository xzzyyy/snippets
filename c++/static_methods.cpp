#include <iostream>
#include <map>
using namespace std;

class Security;

class GmdApi {
    // it is possible to use incomplete types in fields before instantiation
    // if they used as pointers under the hood
    map<string, Security> dict;
    // but this will generate
    // error: field 'sec' has incomplete type 'Security'
    // Security sec;                
public:
    Security& getSmthg(const string& key) { return dict[key]; }
};

class Security {
    int int_v;
public:
    Security() : int_v(5) {}
    Security(int arg) : int_v(arg) {}
    template<typename T> static void func(T arg);
    int getNum() const { return int_v; }
};

// in definition of static methods we should not use static keyword
// error: cannot declare member function 'static void Security::func(T)' to have static linkage [-fpermissive]
template<typename T> /*static*/ void Security::func(T arg) {
    cout << "inside func | arg: " << arg << endl;
}

int main(void) {
    Security::func(5);
    Security::func(12.3);
    Security::func("gopa");
    
    GmdApi gmd_api;
    cout << gmd_api.getSmthg("gopa2").getNum() << endl;
}
