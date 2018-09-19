//
// Created by Macleod,Alasdair John on 9/19/18.
//
#include "main.h"

int main()
{
    double type_I = 0.01;
    double type_II = 0.01;
    double nu1 = 0.01;
    double nu2 = 0.01;
    double lambda = 2;

    double *type_Iptr;
    double *type_IIptr;
    double *nu1ptr;
    double *nu2ptr;
    double *lambdaptr;


    fpow(type_Iptr, type_IIptr, nu1ptr, nu2ptr, lambdaptr);
    printf("Hello, World! lambda is %f\n", *lambdaptr);
    printf("Hello, World! lambda is %f\n", lambda);
    return 0;

}