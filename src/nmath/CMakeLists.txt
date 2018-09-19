cmake_minimum_required(VERSION 3.12)
project(cfpow)

set(CMAKE_C_STANDARD 99)

add_library(nmath bd0.c chebyshev.c cospi.c dbeta.c dbinom.c d1mach.c dnorm.c dpois.c dpq.h fmax2.c fmin2.c i1mach.c lbeta.c lgamma.c lgammacor.c log1p.c mlutils.c nmath.h pbeta.c pchisq.c pf.c pgamma.c pnorm.c ppois.c qbeta.c qnorm.c qpois.c stirlerr.c toms708.c types.h)