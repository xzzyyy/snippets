#include <iostream>
#include <thread>

int main()
{
    auto cores = std::thread::hardware_concurrency();
    std::cout << "number of cores: " << cores << std::endl;
}
