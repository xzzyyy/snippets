#include <iostream>
// Coliru: removes warning
// boost/bind.hpp:36:1: note: '#pragma message: The practice of declaring the Bind placeholders (_1, _2, ...) in
// the global namespace is deprecated
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
using namespace std;

typedef boost::asio::deadline_timer Timer;
typedef Timer::time_type Time;
typedef boost::posix_time::time_duration Duration;
typedef boost::asio::io_service Service;

bool gate_closed = true;

string cur_time() {
    return to_simple_string(Timer::traits_type::now());
}

void func(int val) {
    cout << cur_time() << " | func: " << val << endl;
    gate_closed = false;
}

int main() {
    Service service;   
    Time time_now = Timer::traits_type::now();
    Duration interval = boost::posix_time::seconds(4);      // 5 seconds get expired on Coliru

    Timer timer(service, time_now + interval);
    timer.async_wait(boost::bind(&func, 666));
    cout << cur_time() << " | scheduled" << endl;

    // this should be after timer.async_wait(...) because without task io_service has nothing to do and returns
    // immediately
    service.run();
    cout << cur_time() << " | finishing; gate_closed: " << boolalpha << gate_closed << endl;
}