#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#define WIDTH 512
#define HEIGHT 512

typedef struct s_info
{
    mlx_t       *mlx;
    mlx_image_t *image;
    int         width;
    int         height;
    double      xpos;
    double      ypos;
}   t_info;

typedef struct Complex 
{
    double real;
    double imag;
} complex_t;

complex_t   comp_sum(complex_t z1, complex_t z2);
complex_t   comp_mul(complex_t z1, complex_t z2);