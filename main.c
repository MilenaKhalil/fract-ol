/* ************************************************************************** */
/*	                                                                        */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikhalil <mikhalil@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 23:09:01 by mikhalil      #+#    #+#                 */
/*   Updated: 2023/05/03 20:11:08 by mikhalil      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	hook(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	arrows_check(info);
	colors_check(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_I))
	{
		info->iter += 10;
		image(info->k, info->image, info);
	}
	if (info->width != info->mlx->width || info->height != info->mlx->height)
	{
		info->xpos /= info->width;
		info->width = (double)info->mlx->width;
		info->xpos *= info->width;
		info->ypos /= info->height;
		info->height = (double)info->mlx->height;
		info->ypos *= info->height;
		mlx_resize_image(info->image, info->width, info->height);
		image(info->k, info->image, info);
	}
}

bool	lyap_check(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return (1);
	while (i < ft_strlen(str))
	{
		if (str[i] != 'A' && str[i] != 'B')
			return (1);
		i++;
	}
	return (0);
}

int	input_manage(char **argv, int argc, t_info *info)
{
	if (!ft_strncmp(argv[1], "M", ft_strlen(argv[1])) && argc != 2)
		return (write(2, "Error, there should be no arguments\n", 37));
	if (!ft_strncmp(argv[1], "L", ft_strlen(argv[1]))
		&& (argc != 3 || lyap_check(argv[2])))
		return (write(2, "Error, pas string with A and B as an argument\n", 47));
	if (!ft_strncmp(argv[1], "J", ft_strlen(argv[1]))
		&& (argc != 4 || get_num(argv, info)))
		return (write(2,
				"Error, pas 2 numbers from 0 to 2 as an argument\n", 49));
	if (ft_strncmp(argv[1], "M", ft_strlen(argv[1]))
		&& ft_strncmp(argv[1], "L", ft_strlen(argv[1]))
		&& ft_strncmp(argv[1], "J", ft_strlen(argv[1])))
		return (write(2, "Error, put the name of fractal M, J or L\n", 42));
	return (0);
}

bool	input_check(int argc, char **argv, t_info *info)
{
	unsigned long	i;

	i = 0;
	if (argc == 1)
		return (write(1, "L, M, J\n", 8));
	input_manage(argv, argc, info);
	if (!ft_strncmp(argv[1], "M", ft_strlen(argv[1])) && argc == 2)
		return (0);
	if (!ft_strncmp(argv[1], "L", ft_strlen(argv[1])) && argc == 3
		&& argv[2][0] != 0)
	{
		while (i < ft_strlen(argv[2]))
		{
			if (argv[2][i] != 'A' && argv[2][i] != 'B')
				return (1);
			i++;
		}
		return (0);
	}
	if (!ft_strncmp(argv[1], "J", ft_strlen(argv[1])) && argc == 4)
		return (get_num(argv, info));
	return (1);
}

int32_t	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_info		info;
	mlx_image_t	*img;

	if (input_check(argc, argv, &info))
		exit(EXIT_FAILURE);
	mlx = mlx_init(WIDTH, HEIGHT, "FRACTOL", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		exit(EXIT_FAILURE);
	new_info(&info, mlx, img, argv);
	mlx_image_to_window(mlx, img, 0, 0);
	image(info.k, info.image, &info);
	mlx_cursor_hook(mlx, &mouse_pos, &info);
	mlx_scroll_hook(mlx, &scroll_pos, &info);
	mlx_loop_hook(mlx, &hook, &info);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
