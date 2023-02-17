// aggregate initialization of simple class type
#include <iostream>
using namespace std;

int main(void) {
    struct LevelData { double _p; int _s; }; LevelData ld = { 1.1, 2 };  
    
    cout << ld._p << endl;
    cout << ld._s << endl;
}