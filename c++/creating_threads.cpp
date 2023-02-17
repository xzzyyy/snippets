// creating threads
// each thread has its own stack for every function
// it's impossible to have address of "reference variable" (because it is alias)
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

string str = "gopa";

void func()
{
    thread::id th_id = this_thread::get_id();
    const string& s_ref = str;
    
    this_thread::sleep_for(1s);
    cout << th_id << ' ' << &th_id << ' ' << &s_ref << endl;
    this_thread::sleep_for(1s);
    cout << th_id << ' ' << &th_id << ' ' << &s_ref << endl;
    this_thread::sleep_for(1s);
    cout << th_id << ' ' << &th_id << ' ' << &s_ref << endl;
}

int main()
{
    thread t1(func), t2(func);
    t1.join();
    t2.join();
}