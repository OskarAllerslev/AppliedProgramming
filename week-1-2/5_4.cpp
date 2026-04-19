#include <cmath>
#include <cassert>

double calc_mean(double a[], int length){
    double sum = 0;

    for(int i = 0; i<length; i++)
    {
        sum += a[i];
    }
    return sum / (double)(length);
}

double calc_std(double a[], int length){

    assert(length > 1);

    double sum = 0;
    double mean = calc_mean(a, length);
    double res;

    for (int i = 0; i < length; i++)
    {
        sum += std::pow(a[i] - mean, 2);
    }

    res = std::sqrt( (double)(1)/(length - 1) * sum);
    return res;
}
