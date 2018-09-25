/* Licence: CC0 1.0 Universal 
   http://creativecommons.org/publicdomain/zero/1.0/legalcode

=========================================================================
This program is documented in the paper of A. Baharev, S. Kemeny,
On the computation of the noncentral F and noncentral beta distribution;
Statistics and Computing, 2008, 18 (3), 333-340.
http://dx.doi.org/10.1007/s11222-008-9061-3

Preprint of this paper is available at http://reliablecomputing.eu

My e-mail address is: (my first name) dot (my last name) at gmail dot com

*/

/* This program depends on the following functions of R */
/*
double pf(double x, double n1, double n2, int lower_tail, int log_p);
double qbeta(double alpha, double p, double q, int lower_tail, int log_p);
double dbeta(double x, double a, double b, int give_log);
double pbeta(double x, double pin, double qin, int lower_tail, int log_p);
double dpois(double x, double lambda, int give_log);
double qpois(double p, double lambda, int lower_tail, int log_p);
*/
#include "nmath/dpq.h"
#include "nmath/nmath.h"

/*
2-moment central F approximation; Patnaik P. B. 1949.
The non-central chi-square and F distribution and their applications;
Biometrika; 36: 202-232.
*/
static double patnaik2(double x, double nu1, double nu2, double lambda) {

  return pf( x/(1+lambda/nu1), (nu1+lambda)*((nu1+lambda)/(nu1+2*lambda)), nu2, 1, 0);
}

/*
This function gives an initial value of lambda for the Newton iteration.
First, the lambda value is bracketed, then bisection is used to find a 
better approximation. This function uses the 2-moment central F 
approximation of Patnaik.
*/
static double guess(double prob, double y, double nu1, double nu2) {

  double x;
  double lambdal;
  double lambdam;
  double lambdau;
  double fl;
  double fm;
  double fu;
  int itr_cnt;

  /* FIXME: cancellation ? */
  x = nu2*y/(nu1*(1.0-y));
  lambdal = 0.0;
  lambdau = 1.0;

  fl = pf(x, nu1, nu2, 1, 0);

  /* In this case there is no solution */
  if (fl < prob) {
    printf("no solution (most likely a bug)");
  }

  fu = patnaik2(x, nu1, nu2, lambdau);

  /* Bracketing lambda: lambdal <= lambda <= lambdau */
  for (itr_cnt=1; ((fl-prob)*(fu-prob)>0.0)&&itr_cnt<=17; ++itr_cnt)
  {
    fl = fu;
    lambdal = lambdau;
    lambdau = 2.0*lambdau;
    fu = patnaik2(x,nu1,nu2,lambdau);
  }

  if (itr_cnt == 18) {
    printf("failed to bracket lambda, it is likely to be LARGE");
  }

  /* find a better approximation of lambda by bisection */

  lambdam = (lambdal + lambdau)/2.0;

  for (itr_cnt=1; (((lambdau-lambdal)>1.0e-4*lambdau)&&((lambdau-lambdal) > 0.001))&&(itr_cnt<=29); ++itr_cnt)
  {

    fm = patnaik2(x, nu1, nu2, lambdam);

    if ((fm-prob)*(fu-prob) < 0.0) {
      fl = fm;
      lambdal = lambdam;
    }
    else {
      fu = fm;
      lambdau = lambdam;
    }

    lambdam = (lambdal + lambdau)/2.0;

  }

  if (itr_cnt == 30) {
    printf("failed to find initial guess");
  }

  return lambdam;
}

/*
Given prob, x, a and b, this function returns the corresponding 
noncentrality parameter of the noncentral beta distribution.

I.e. the following equation

I_x(a, b, lambda) = prob

is solved for lambda with Newton iteration.

This function works just fine when supplied with meaningful input
data (and from practically meaningful range) but may easily crash
if not. Please be nice.
*/
static double ncbeta(double prob, double x, double a, double b) {

  double ql;
  double qu;
  double c;
  double d;
  double p;
  double lambda;
  double lambda_new;
  double k;
  double f;
  double g;
  double mu;
  double eps;
  double eps2;
  int itr_cnt;

  lambda_new = guess(prob, x, 2.0*a, 2.0*b);

  /* FIXME: are these tolerances OK ?  */
  eps  = 1.0e-7;
  eps2 = 1.0e-6;

  itr_cnt = 0;

  do {

    lambda = lambda_new;

    mu = lambda/2.0;

    ql = qpois(eps, mu, 1, 0);

    qu = qpois(eps, mu, 0, 0);

    k = qu;

    c = pbeta(x, a+k, b, 1, 0);

    d = x*(1.0-x)/(a+k-1.0)*dbeta(x, a+k-1, b, 0);

    p = dpois(k, mu, 0);

    f=p*c;

    p = k/mu*p;

    g = p*d;

    for (k = qu-1; k >= ql; --k) {

      c=c+d;

      d=(a+k)/(x*(a+k+b-1))*d;

      f=f+p*c;

      p=k/mu*p;

      g=g+p*d;

    }

    /* Newton step */
    lambda_new = lambda+2.0*(f-prob)/g;

    if (lambda_new <= 0.0)
      lambda_new = lambda/2.0;

    ++itr_cnt;
  }
  while ((fabs(lambda_new-lambda) > eps2*lambda_new)&&(itr_cnt<=10));

  if (itr_cnt == 11) {
    printf("newton iteration failed");
  }

  return lambda_new;

}

void fpow(double* type_I, double* type_II, double* nu1, double* nu2, double* lambda) {

  if ( ! ( ((*type_I ) >= 0.001) && ((*type_I ) <= 0.999)))
    printf("probabilty of type I error should be between 0.001 and 0.999");

  if ( ! ( ((*type_II) >= 0.001) && ((*type_II) <= 0.999)))
    printf("probabilty of type II error should be between 0.001 and 0.999");

  if ((*nu1)<=0.0)
    printf("nu1 must be positive");

  if ((*nu2)<=0.0)
    printf("nu2 must be positive");

  if (((*type_I)+(*type_II)) > 0.9999) {

    printf("sum of probability of type I and type II error exceeds 0.9999");
  }
  else {

    *lambda = ncbeta(*type_II, qbeta(*type_I, *nu1/2.0, *nu2/2.0, 0, 0), *nu1/2.0, *nu2/2.0);
  }

}

double probf(double type_I, double a, double b, double lambda) {
//    step3 Calculate the greatest k_1 and the lowest k_2 such that (2) and (3) hold.
//    Step 4. Initializations.
//    Step 4.2 k = k_2
//    Step 4.3. µ = λ/2
//    Step 4.4. c = I_x(a + k,b)
//    Step 4.5. d = x (1 − x )/(a + k − 1) ⋅ Beta(x,a + k − 1, b)
//    Step 4.6. (e^-µ k µ^k)/k!
//    Step 4.7. f = p ⋅ c
//    Step 4.8. p = k / µ ⋅ p
//    Step 5. For k = k2 −1, k2 − 2 , …, k_1, do steps 5.1 to 5.5.
//    Step 5.1. c = c + d
//    Step 5.2. d = ( a + k )/ (x ⋅(a + k + b − 1))⋅d
//    Step 5.3. f = f + p ⋅c
//    Step 5.4. p = k / µ ⋅ p
//    4.2, 4.9, 5.5, 6, 7, 8; the cdf value is the value of
//    f obtained in the last evaluation of step 5.3.

    double x = qbeta(type_I, a, b, 0, 0);
    double ql;
    double qu;
    double c;
    double d;
    double p;
    double k;
    double f;
    double g;
    double mu;
    double eps;
    double eps2;
    int itr_cnt;

    /* FIXME: are these tolerances OK ?  */
    eps  = 1.0e-7;
    eps2 = 1.0e-6;

    itr_cnt = 0;

    do {

        mu = lambda/2.0;

        ql = qpois(eps, mu, 1, 0);

        qu = qpois(eps, mu, 0, 0);

        k = qu;

        c = pbeta(x, a+k, b, 1, 0);

        d = x*(1.0-x)/(a+k-1.0)*dbeta(x, a+k-1, b, 0);

        p = dpois(k, mu, 0);

        f=p*c;

        p = k/mu*p;

        for (k = qu-1; k >= ql; --k) {

            c=c+d;

            d=(a+k)/(x*(a+k+b-1))*d;

            f=f+p*c;

            p=k/mu*p;
        }
        ++itr_cnt;
    }

    while (itr_cnt<=10);

    if (itr_cnt == 11) {
        printf("newton iteration failed");
    }

    return f;
}

