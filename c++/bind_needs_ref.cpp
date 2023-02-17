#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
// removes warning "boost/bind.hpp:36:1: note: '#pragma message: The practice of declaring the Bind placeholders
// (_1, _2, ...) in the global namespace is deprecated"
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>
using namespace std;

typedef boost::asio::deadline_timer Timer;

string cur_time() {
    return to_simple_string(Timer::traits_type::now());
}

void func(const string& prefix, int& val) {
    cout << cur_time() << " | " << prefix << ": " << &val << endl;
}

int main() {
    cout << "Boost version: " << BOOST_VERSION << endl;
    
    int v = 666;
    cout << cur_time() << " | outside func: " << &v << endl;
    boost::asio::io_service svc;

    Timer timer(svc);                                               
    timer.expires_from_now(boost::posix_time::seconds(1));
    timer.async_wait(boost::bind(&func, boost::cref("without ref(...)"), v));
    svc.run();

    svc.restart();                                                  // TODO how this implemented in publisherProto?
    timer.expires_from_now(boost::posix_time::seconds(1));
    timer.async_wait(boost::bind(&func, boost::cref("with ref(...)"), boost::ref(v)));
    svc.run();
}