#include <cmath>
// #include <cassert>

double calc_mean(double a[], int length){
    double sum = 0;

    for(int i = 0; i<length; i++)
    {
        sum += a[i];
    }
    return sum / (double)(length);
}

double calc_std(double a[], int length) {

  // assert(length > 1);
  if (length <= 1) {
    return 0.0;
  }

  double sum = 0.0;
  double mean = calc_mean(a, length);
  double res;

  /*
  1/(N-1) sum_{n=1}^N (X_i - \mu)^2
  */

  for (int i = 0; i < length; i++) {
    sum += std::pow(a[i] - mean, 2);
  }

  res = std::sqrt((double)(1) / (length - 1) * sum);
  return res;
}
