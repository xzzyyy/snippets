#include <iostream>
#include <random>

int main() {
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    std::mt19937 engine;
    
    for (int i = 0; i < 10; ++i) {
        double v = dist(engine);
        std::cout << "value: " << v << ", abs: " << abs(v) << ", std::abs: " << std::abs(v) << std::endl;
    }
}