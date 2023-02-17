#include <iostream>
#include <unordered_map>
using namespace std;


int main(int, char*[]) {
    unordered_map<int, double> hash_map;
	cout << "max load factor: " << hash_map.max_load_factor() << endl;
    cout << "size: " << hash_map.size() << ", bucket count: " << hash_map.bucket_count() << endl;
    
    for (int i = 0; i < 100; ++i) {
        hash_map[i] = i * 1.5;
        cout << "size: " << hash_map.size() << ", bucket count: " << hash_map.bucket_count() << ", load factor: " << hash_map.load_factor() << endl;
    }
}

// rehashing sizes: 1, 13, 29, 59, 127