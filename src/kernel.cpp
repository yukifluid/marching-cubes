#include "kernel.hpp"

double Poly6(double r, double h)
{
    double a = 315.0/(64.0*PI*pow(h, 9.0));	
    if(r < 0.0 || h < r) return 0.0;
    double q = h*h - r*r;
    double y = a*q*q*q;
    return y;
}