#include <iostream>
#include <string>
#include <memory>
using namespace std;

class GenericStack
{
public:
    GenericStack();
    ~GenericStack();
    void push(void* object);
    void* pop();
    bool empty() const;
private:
    struct StackNode {
        void* data;                                     // data at this node
        StackNode* next;                                // next node in list
        StackNode(void* newData, StackNode* nextNode)
            : data(newData), next(nextNode) {}
    };
    StackNode* top;                                     // top of stack
    GenericStack(const GenericStack& rhs);              // prevent copying and
    GenericStack& operator=(const GenericStack& rhs);   // assignment (see Item 27)
};

GenericStack::GenericStack()
    : top(NULL) {}                                      // initialize top to null
    
void GenericStack::push(void* object) {
    top = new StackNode(object, top);                   // put new node at front of list
}

void* GenericStack::pop() {
    StackNode* topOfStack = top;                        // remember top node
    top = top->next;
    void* data = topOfStack->data;                      // remember node data
    delete topOfStack;
    return data;
}

GenericStack::~GenericStack() {                         // delete all in stack
    while (top) {
        StackNode* toDie = top;                         // get ptr to top node
        top = top->next;                                // move to next node
        delete toDie;                                   // delete former top node
    }
}

bool GenericStack::empty() const {
    return top == NULL;
}

template<class T>
class Stack: private GenericStack {
public:
    void push(T* objectPtr) { GenericStack::push(objectPtr); }
    T* pop() { return static_cast<T*>(GenericStack::pop()); }
    bool empty() const { return GenericStack::empty(); }
};

class Cat {
    int n;
public:
    Cat(int n) : n(n) {}
    string meow() const;
};

string Cat::meow() const {
    return string("meow ") + to_string(n);
}

int main(void) {
    int nums[] = { 1, 2, 3 };
    Stack<int> intStack;
    intStack.push(&nums[1]);
    intStack.push(&nums[2]);
    intStack.push(&nums[0]);
    cout << *intStack.pop() << ' ' << *intStack.pop() << ' ' << *intStack.pop() << endl;
    
    shared_ptr<Cat> cats[] = { make_shared<Cat>(1), make_shared<Cat>(2), make_shared<Cat>(3) };
    Stack<Cat> catStack;
    catStack.push(cats[1].get());
    catStack.push(cats[2].get());
    catStack.push(cats[0].get());
    cout << catStack.pop()->meow() << ' ' << catStack.pop()->meow() << ' ' << catStack.pop()->meow() << endl;
}