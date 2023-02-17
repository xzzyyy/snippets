#include <fstream>
#include <string>
using namespace std;

int main() {
	static const string TEST_STR = "test";
	
	// ofstream s(TEST_STR);        // error when c++03
	ofstream s(TEST_STR.c_str());
	s << "hello" << endl;
}