#include <algorithm>
#include <random>
#include <array>
#include <iostream>

void bin_search() {
    std::random_device r;
    std::default_random_engine re(r());
    std::uniform_real_distribution<> distribution(0.0, 100.0);
    std::uniform_real_distribution if_double_deduced(0.0, 100.0);

    std::array<double, 100> arr{};
    for (double &val : arr)
        val = distribution(re);

    double to_find = arr.front();
    std::sort(arr.begin(), arr.end());

    std::cout << "binary_search res: " << std::boolalpha <<
              std::binary_search(arr.cbegin(), arr.cend(), to_find) << std::endl;
}

int main() {
    bin_search();
    std::cerr.flush();      // TODO why no flush function in output trace?
}
