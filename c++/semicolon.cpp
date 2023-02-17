#include <iostream>
using namespace std;

struct Semicolon {
    Semicolon() {};
    void print() { cout << "hello" << endl; };
};

int main() {
    Semicolon s;
    s.print();
}