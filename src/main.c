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


    fpow(&type_I, &type_II, &nu1, &nu2, &lambda);
    printf("\n lambda is %f\n", lambda);
    return 0;

}