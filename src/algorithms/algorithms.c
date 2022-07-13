#include "algorithms.h"

long factorial(int n) {
    long result = 1;
    for (long i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double map_range(double a_1, double a_2, double b_1, double b_2, double s) {
    return b_1 + (s - a_1) * (b_2 - b_1) / (a_2 - a_1);
}
