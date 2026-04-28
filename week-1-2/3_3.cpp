
#include <cassert>
#include <fstream>
#include "3_3.h"

void implicit_Euler(int n)
{
    assert(n > 1);

    double h = (double)(1) / (double)(n); 
    double x = 0.0;
    double y = 1.0;

    std::ofstream output("xy.dat");
    assert(output.is_open()); 

    output << x << "," << y << "\n";

    for (int i = 1; i <= n; i++) 
    {
        x = i * h;             
        y = y / (1 + h);      
        output << x << "," << y << "\n";
    }
    
    output.close();
}