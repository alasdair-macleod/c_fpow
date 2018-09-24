//
// Created by Macleod,Alasdair John on 9/19/18.
//
#include "main.h"

int main()
{
    double type_I = 0.01;
    double type_II = 0.01;
    double nu1 = 1;
    double nu2 = 2;
    double lambda = 2;
    double f = -1;


    fpow(&type_I, &type_II, &nu1, &nu2, &lambda);
    f = probf(type_I, type_II, nu1, nu2);

    printf("\n lambda is %f\n", lambda);
    printf("\n p is %f\n", f);
    return 0;

}