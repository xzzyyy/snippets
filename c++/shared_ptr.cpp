#include <memory>
#include <iostream>
using namespace std;

class TestClass {
    int id;
public:
    TestClass(int id) : id(id) { cout << "TestClass [" << id << "] constructor" << endl; }
    ~TestClass() { cout << "TestClass [" << id << "] destructor" << endl; }
};

int main() {
    TestClass* p1 = new TestClass(1);
    TestClass* p2 = new TestClass(2);
    shared_ptr<TestClass> sp11(p1);
    shared_ptr<TestClass> sp12(sp11);
    shared_ptr<TestClass> sp2(p2);
    cout << "p1 count: " << sp11.use_count() << endl;
    cout << "p2 count: " << sp2.use_count() << endl;
}