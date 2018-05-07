#include <stdio.h>
#include <math.h>
#include "functions_five.h" 

double f(double x) {
    x += 2;
    return x;
}

double g(double x) {
    double y = pow(x, 2);
    return y;
}

double h(double x) {
    double z = pow(x, 2);
    double y = z + 4;
    return y;
}

double k(double x) {
    double z = pow(x, 2);
    double y = z + x + 4;
    return y;
}

double j(double x) {
    double z = pow(x, 2);
    double y = z+5;
    return y;
}