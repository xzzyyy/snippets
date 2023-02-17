#include <iostream>
using namespace std;

typedef enum eCacheClearBitMask
{
    GMD_CLEARQUOTES_BITMASK=0x01,
    GMD_CLEARTRADES_BITMASK=0x02,
    GMD_CLEARIMBALANCE_BITMASK=0x04,
    GMD_CLEARPEGGEDORDER_BITMASK=0x08,
    GMD_CLEARPRICELEVEL_BITMASK=0x10
} CacheClearBitMask;

int main(void) {
    // this allowed only in C++11, in C++03 results in error:
    // 'eCacheClearBitMask' is not a class or namespace
    cout << eCacheClearBitMask::GMD_CLEARIMBALANCE_BITMASK << endl;
}