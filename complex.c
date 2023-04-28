/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complex.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:16 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/04/25 22:51:07 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	comp_sum(t_complex z1, t_complex z2)
{
	t_complex	z3;

	z3.real = z1.real + z2.real;
	z3.imag = z1.imag + z2.imag;
	return (z3);
}

t_complex	comp_mul(t_complex z1, t_complex z2)
{
	t_complex	z3;

	z3.real = z1.real * z2.real - z1.imag * z2.imag;
	z3.imag = z1.real * z2.imag + z1.imag * z2.real;
	return (z3);
}

t_complex	count(t_complex z1, t_complex z2)
{
	return (comp_sum(comp_mul(z1, z1), z2));
}

bool	check(t_complex z1)
{
	if (sqrt(pow(z1.real, 2) + pow(z1.imag, 2)) > 3)
		return (0);
	return (1);
}
