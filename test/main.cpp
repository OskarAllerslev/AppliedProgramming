

#include <iostream>
#include <cmath>

int main () {
    std::cout << "dette er bare en test" << std::endl;

    double start = 0.0;
    double rate = 0.01;
    int aar = 10;

    double fremtid = start * std::pow(1 + rate, aar); 

    std::cout << "fremtidsværdi er: " << fremtid << std::endl;
    return 0;
}
