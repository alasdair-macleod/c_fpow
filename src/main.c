//
// Created by Macleod,Alasdair John on 9/19/18.
//
#include "main.h"

int main()
{
    double type_I = 0.05;
    double a = 0.5;
    double b = 0.5;
    double f;

    f = probf(type_I, a, b, 15.848931925);
    printf("\n prob f is %f\n", f);

    f = probf(type_I, a, b, 25.11886432);
    printf("\n prob f is %f\n", f);

    f = probf(type_I, a, b, 3981.0717055);
    printf("\n prob f is %f\n", f);


    f = probf(0.05,1/2.0,1/2.0,10);
    printf("\n prob f is %f\n", f);
    f = probf(0.05,1/2.0,1/2.0,15.848931925);
    printf("\n prob f is %f\n", f);
    f = probf(0.05,1/2.0,1/2.0,25.118864315);
    printf("\n prob f is %f\n", f);
    f = probf(0.05,1/2.0,1/2.0,39.810717055);
    printf("\n prob f is %f\n", f);
    f = probf(0.05,1/2.0,1/2.0,63.095734448);
    printf("\n prob f is %f\n", f);
    f = probf(0.05,1/2.0,1/2.0,100);
    printf("\n prob f is %f\n", f);
    f = probf(0.05,1/2.0,1/2.0,158.48931925);
    printf("\n prob f is %f\n", f);
    f = probf(0.05,1/2.0,1/2.0,251.18864315);
    printf("\n prob f is %f\n", f);

    return 0;

}