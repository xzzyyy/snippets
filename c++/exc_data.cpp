#include <stdexcept>
#include <sstream>
#include <boost/log/trivial.hpp>
using namespace std;

string readUntilDelim(stringstream& ss) {
    constexpr size_t MAXLEN = 100u;
    char desc[MAXLEN + 1];
    ss.get(desc, MAXLEN, '|');
    ss.get();
    return desc;
}

void parse(stringstream&& ss) {
    int ec;
    ss >> ec;
    ss.get();
    BOOST_LOG_TRIVIAL(error) << "error code: " << ec;
    BOOST_LOG_TRIVIAL(info) << "description: [" << readUntilDelim(ss) << ']';
    BOOST_LOG_TRIVIAL(debug) << "skipped: [" << readUntilDelim(ss) << ']';
}

int main() {
    try {
        throw runtime_error("3|error reason etc|garbage");
    } catch (const runtime_error& exc) {
        parse(stringstream(exc.what()));
    }
    
    try {
        throw runtime_error("5|different error etc|garbage for test");
    } catch (const runtime_error& exc) {
        parse(stringstream(exc.what()));
    }
}