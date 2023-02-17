#include <iostream>
#include <array>
#include <vector>

template<typename T> struct Vector3D
{
    Vector3D() = default;                   // TODO will it be created automatically for POD types ? 
                                            // (it depends on other declared constructors instead)
    template<typename T2> Vector3D(T2 arg)
    {
        coords[0] = arg[0];
        coords[1] = arg[1];
        coords[2] = arg[2];
    }
    void operator=(const Vector3D& v)       // uncanonical operator signature
    {
        coords[0] = v[0];
        coords[1] = v[1];
        coords[2] = v[2];
        std::cout << "custom `operator=`" << std::endl;
    }
    const T& operator[](int idx) const
    {
        return coords[idx];
    }
private:
    std::array<T, 3> coords;
};

template<typename T> struct Vector3DTest
{
private:
    std::array<T, 3> coords;                // default constructor implicitly created of no other constructors declared
};

int main()
{
    std::vector<int> vec_int = {1, 2, 3};
    Vector3D<double> c_inst(vec_int);
    std::cout << "res: " << c_inst[0] << ", " << c_inst[1] << ", "  << c_inst[2] << std::endl;
    
    Vector3D<double> c_inst2;
    c_inst2 = c_inst;               // `operator=` with uncanonical signature replaces implicitly created
    // (c_inst2 = c_inst)[0];       // error
    std::cout << "res: " << c_inst2[0] << ", " << c_inst2[1] << ", "  << c_inst2[2] << std::endl;
    
    Vector3DTest<int> vec_test;
}
