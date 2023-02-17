#include <iostream>
using namespace std;

static const size_t ARR_SIZE = 1000u;
static const int CALLS_CNT = 10;

void func(int lvl)
{
    cout << "---lvl" << lvl << "---" << endl;
    
    char arr[1000];
    int garbage_cnt = 0;
    for (size_t i = 0; i < ARR_SIZE; ++i)
        if (arr[i] != 0)
            ++garbage_cnt;
    cout << "garbage symbols: " << garbage_cnt << '/' << ARR_SIZE << endl;
            
    if (lvl == CALLS_CNT)
        return;
    else
        func(lvl + 1);
}

int main(int argc, char* argv[])
{
    func(0);
    
    char c = char();
    int i = int();
    cout << "value initialization | char: " << hex << static_cast<unsigned>(c) << ", int: " << i << endl;
}

// ---lvl0---
// garbage symbols: 560/1000
// ---lvl1---
// garbage symbols: 601/1000
// ---lvl2---
// garbage symbols: 627/1000
// ---lvl3---
// garbage symbols: 503/1000
// ---lvl4---
// garbage symbols: 502/1000
// ---lvl5---
// garbage symbols: 504/1000
// ---lvl6---
// garbage symbols: 549/1000
// ---lvl7---
// garbage symbols: 516/1000
// ---lvl8---
// garbage symbols: 502/1000
// ---lvl9---
// garbage symbols: 503/1000
// ---lvl10---
// garbage symbols: 503/1000
// value initialization | char: 0, int: 0