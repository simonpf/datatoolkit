#include <iostream>

#include "matlab.h"

int main()
{
    auto data = read_matlab_data<double>("matlab.mat");
    std::cout << data << std::endl;
}
