#include <iostream>
#include <string>
using namespace std;

void func(string const&& str) {
    cout << "const r-value arg func: " << str << endl;
}

void func(string&& str) {
    cout << "modifiable r-value arg func: " << str << endl;
}

int main() {
    func(string{"gopa"});
}
