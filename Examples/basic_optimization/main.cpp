#include <iostream>
#include "GeneticAlgorithm.hpp"

class Test {
public:
    Test() {};


};

int main()
{
    std::cout << "Hello Example Project" << std::endl;
    auto test = GA_Cpp::GeneticAlgorithm<Test>();
}