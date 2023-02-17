#include <iostream>
#include <vector>
using namespace std;

int main() {
	struct Test { 
		int _val; 
		Test(int val) : _val(val) {} 
	};
	
	// error if -std=c++03
	// template argument for 'template<class> class std::allocator' uses local type 'main()::Test'
	vector<Test> test_v;																		
	test_v.push_back(Test(1)); test_v.push_back(Test(11)); test_v.push_back(Test(5));
	for (size_t i = 0; i < test_v.size(); ++i)
		cout << test_v[i]._val << endl;
}