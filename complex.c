#include "fractol.h"

complex_t   comp_sum(complex_t z1, complex_t z2)
{
    complex_t   z3;

    z3.real = z1.real + z2.real;
    z3.imag = z1.imag + z2.imag;
    return (z3);
}

complex_t   comp_mul(complex_t z1, complex_t z2)
{
    complex_t   z3;

    z3.real = z1.real * z2.real - z1.imag * z2.imag;
    z3.imag = z1.real * z2.imag + z1.imag * z2.real;
    return (z3);
}