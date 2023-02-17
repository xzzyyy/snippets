#include <iostream>
#include <typeinfo>
using namespace std;

int main() {
    int i32 = -2;
    unsigned u32 = 0;
    short i16 = -2;
    unsigned short u16 = 1;
    cout << "int: " << typeid(i32).name() << ", unsigned: " << typeid(u32).name() << 
            ", short: " << typeid(i16).name() << ", unsigned short: " << typeid(u16).name() << endl;
    
    cout << "int + unsigned: " << typeid(i32 + u32).name() << endl;
    cout << "short + unsigned: " << typeid(i16 + u32).name() << endl;
    cout << "int + unsigned short: " << typeid(i32 + u16).name() << endl;
}