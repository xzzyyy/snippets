// typeid
#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
    cout << "char: " << typeid(char).name() << endl;                            // c
    cout << "unsigned char: " << typeid(unsigned char).name() << endl;          // h
    cout << "short: " << typeid(short).name() << endl;                          // s
    cout << "unsigned short: " << typeid(unsigned short).name() << endl;        // t
    cout << "int: " << typeid(int).name() << endl;                              // i
    cout << "unsigned: " << typeid(unsigned).name() << endl;                    // j
    cout << "long: " << typeid(long).name() << endl;                            // l
    cout << "unsigned long: " << typeid(unsigned long).name() << endl;          // m
    cout << "cout: " << typeid(cout).name() << endl;                            // So
    cout << "\"str\": " << typeid("str").name() << endl;                        // A4 c
    cout << endl;
    
    cout << "const char: " << typeid(const char).name() << endl;                // c (same as char)
    cout << "char*: " << typeid(char*).name() << endl;                          // Pc
    cout << "char const*: " << typeid(char const*).name() << endl;              // PKc
    cout << "char const* const: " << typeid(char const* const).name() << endl;  // PKc (same as char const*)
    cout << endl;
    
    
    cout << "char: " << typeid(char).name() << endl;                            // c
    cout << "char&: " << typeid(char&).name() << endl;                          // c (same as char)
    cout << endl;
    
    cout << "hash_code() for char: " << typeid(char).hash_code() << endl;               // same
    cout << "hash_code() for const char: " << typeid(const char).hash_code() << endl;   // same
}
