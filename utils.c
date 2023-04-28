/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:16 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/04/25 22:59:37 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_rgb(char r, char g, char b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

double	absolut(double num)
{
	if (num > 0)
		return (num);
	else
		return (num * -1);
}

bool	dot_atoi(double *res, char *str, int i, int min)
{
    double  k;
    
	*res = 0;
    k = 1;
	while (str[i])
	{
        if (str[i] == '.' && k == 1)
            k = 10;
        else if (str[i] >= '0' && str[i] <= '9')
        {
		    *res = (*res) * 10 + str[i] - '0';
            if (k != 1)
                k *= 10;
        }
        else
            return (1);
		i++;
	}
    *res = (*res * min) / k;
    if (k > 1)
        *res *= 10;
    if (absolut(*res) >= 2)
        return (1);
	return (0);
}

bool    get_num(char **argv, t_info *info)
{
    double  min;
    int     i;
    int     j;
    int     out;

    j = 0;
    while (j < 2)
    {
        min = 1;
        i = 0;
	    while ((argv[j + 2][i] >= 9 && argv[j + 2][i] <= 13) || argv[j + 2][i] == 32)
		    i++;
	    if (argv[j + 2][i] == '-')
	    {
		    min = -1;
		    i++;
	    }
        if (j == 0)
            out = dot_atoi(&(info->jr), argv[j + 2], i, min);
        else
            out += dot_atoi(&(info->ji), argv[j + 2], i, min);
        j++;
    }
    return (out);
}

void	new_info(t_info *info, mlx_t *mlx, mlx_image_t *img, char **argv)
{
	info->mlx = mlx;
	info->image = img;
	info->width = (double)WIDTH;
	info->height = (double)HEIGHT;
	info->k = 1;
	info->xpos = (2.5 / 4) * WIDTH;
	info->xx = 0;
	info->yy = 2 * (info->height) / (info->width);
	info->fractal = argv[1][0];
    if (argv[1][0] == 'L')
    {
        info->xpos = 0;
        info->yy = 0;
        info->liap = argv[2];
    }
    info->iter = ITER;
	ft_bzero(info->arrows, 2);
	ft_bzero(info->colors, 3);
}
