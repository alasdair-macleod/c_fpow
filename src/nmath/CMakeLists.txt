cmake_minimum_required(VERSION 3.12)
project(cfpow)

set(CMAKE_C_STANDARD 99)

add_library(bd0.c chebyshev.c dbeta.c dbinom.c dpois.c dpq.h fmax2.c fmin2.c lbeta.c lgamma.c lgammacor.c log1p.c nmath.h pbeta.c pchisq.c pf.c pgamma.c qbeta.c qpois.c types.h)