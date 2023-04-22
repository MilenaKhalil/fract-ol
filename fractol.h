/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:11 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/04/22 23:37:36 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <math.h>
# define WIDTH 512
# define HEIGHT 512
# define ITER 300

typedef struct s_info
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			width;
	int			height;
	double		xpos;
	double		ypos;
	double		k;
	double		arrows[2];
	char		colors[3];
}	t_info;

typedef struct Complex
{
	double	real;
	double	imag;
}	t_complex;

t_complex	comp_sum(t_complex z1, t_complex z2);
t_complex	comp_mul(t_complex z1, t_complex z2);
t_complex	count(t_complex z1, t_complex z2);
bool	check(t_complex z1);
int	get_rgb(char r, char g, char b);

#endif