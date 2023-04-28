/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:11 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/04/25 23:05:21 by mikhalil      ########   odam.nl         */
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
# define ITER 200

typedef struct Complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_info
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int	    	iter;
	double      width;
	double      height;
	double		xpos;
	double    	xx;
	double	    yy;
	double      ypos;
	double		k;
	double      arrows[2];
	char	    colors[3];
	char        fractal;
    char        *liap;
    double      jr;
    double      ji;
}	t_info;

t_complex	comp_sum(t_complex z1, t_complex z2);
t_complex	comp_mul(t_complex z1, t_complex z2);
t_complex	count(t_complex z1, t_complex z2);

void	new_info(t_info *info, mlx_t *mlx, mlx_image_t *img, char **argv);
void	mouse_pos(double xpos, double ypos, void *info);
void	scroll_pos(double xdelta, double ydelta, void *info);
void	colors_check(t_info *info);
void	arrows_check(t_info *info);
void	image(double k, mlx_image_t *img, t_info *info);
void    color_pixel(t_info *info, double x, double y, double mul);
void	image(double k, mlx_image_t *img, t_info *info);

bool	check(t_complex z1);
bool    get_num(char **argv, t_info *info);

int		get_rgb(char r, char g, char b);

double	absolut(double num);

#endif
