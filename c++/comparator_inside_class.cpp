// comparator function for algorithm inside class
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct PriceLevel
{
    double p;
    int s;
};

struct OrderBook
{
    typedef vector<PriceLevel> LevelsType;
    LevelsType v;
  
    OrderBook();  
    static bool cmp(const PriceLevel& l, const PriceLevel& r);
    void f();
};

OrderBook::OrderBook()
{
    PriceLevel l1 = { 1.0, 1 };
    PriceLevel l2 = { 2.0, 2 };
    PriceLevel l3 = { 3.0, 3 };
    v.push_back(l1);
    v.push_back(l2);
    v.push_back(l3);
}

bool OrderBook::cmp(const PriceLevel& l, const PriceLevel& r)
{
    return l.p < r.p;
}

void OrderBook::f()
{
    PriceLevel pl = { 1.9, 1 };
    LevelsType::iterator lvl = upper_bound(v.begin(), v.end(), pl, cmp);	// cmp should be static
    if (lvl == v.end())
        cout << "last" << endl;
    else
    {
        cout << lvl->p << endl;
        cout << lvl->s << endl;
    }
}

int main(void) {
    OrderBook ob;
    ob.f();
}