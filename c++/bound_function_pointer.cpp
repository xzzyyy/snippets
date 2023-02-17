#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

bool exit_flag = false;

struct SignalProcessing {
    void act_on_signal(int sig) { cout << "act_on_signal called; sig = " << sig << endl; exit_flag = true; }
    static void act_on_signal_static(int sig) { cout << "act_on_signal_static called; sig = " << sig << endl; 
                                                exit_flag = true; }
};

int main() {
    SignalProcessing sig_proc;
    // signal(SIGINT, sig_proc.act_on_signal);
        // VSCode IntelliSense: a pointer to a bound function may only be used to call the function
        // GCC: error: cannot convert ‘SignalProcessing::act_on_signal’ 
        // from type ‘void (SignalProcessing::)(int)’ to type ‘_sig_func_ptr’ {aka ‘void (*)(int)’}
    signal(SIGINT, sig_proc.act_on_signal_static);
    while (!exit_flag) {
        cout << "waiting ctrl-c..." << endl;
        sleep(1);
    }
}
