#include <iostream>
#include <vector>
using namespace std;

template<class T> class C
{
    vector<T> v;
public:
    C(size_t s)
        : v(s)
    {
    }
    
    void fill(T val)
    {
        // without typename
        // error: need 'typename' before 'DepClass::InnerClass' because 'DepClass' is a dependent scope
        for (typename vector<T>::iterator it = v.begin(); it != v.end(); ++it)
            *it = val;
    }
    
    ~C()
    {
        for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
            cout << *it << ' ';
        cout << endl;
    }
};

int main(void) {
    C<int> c(5);
    c.fill(666);
}