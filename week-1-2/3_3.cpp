
#include <cassert>
#include <fstream>


void implicit_Euler(int n)
{
    // use assert to ensure n > 1
    assert(n  > 1);

    // we should print the result to xy.dat with two columns and compare with y = e^-x 
    double h = (double)(1) / (double)(n); 
    double x = 0.0;
    double y = 1.0;

    std::ofstream output("xy.dat");
    assert(output.is_open());
    output << x << "," << y << std::endl;

    for (int i = 0; i < n; i++) 
    {
        x = i * h;
        y = y / (1 + h);
        output << x << "," << y << std::endl;
    };
    output.close();
}