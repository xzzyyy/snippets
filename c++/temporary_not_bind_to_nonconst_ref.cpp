// temporary cannot be bound to non-const reference
#include <iostream>
using namespace std;
 
// if string&
// error: cannot bind non-const lvalue reference of type 'type1' to an rvalue of type 'type2'
int subscribe(string& sub, const string& sessionId)		
{
    return (sub += sessionId).length() > 5 ? 5 : 0;
}

int main(void) {
    string range = "0G";
    string first = "lalala";
    cout << subscribe(first, string("superbook_") + range) << endl;
}