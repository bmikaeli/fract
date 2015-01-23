/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <bmikaeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:51:02 by bmikaeli          #+#    #+#             */
/*   Updated: 2015/01/21 12:32:34 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "libft.h"
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define BUFF_SIZE    1024
# define WIDTH 1000
# define HEIGHT 1000
# define ECHAP    65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define MINUS 65453
# define PLUS 65451
# define JULIA 42
# define MANDELBROT 84
# define SIERPINSKI 126

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;
typedef struct s_mlx {
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img;
    int bpp;
    int name;
    int color_shift;
    int iteration;
    int img_width;
    float mouse_x;
    float mouse_y;
    int img_height;
    int lock;
    int size_line;
    int endian;
    float Cb;
    float zoom;
    int last_x;
    int last_y;
    float Ca;
} t_mlx;
typedef unsigned long ulong;

void julia(t_mlx *mlx);

void mandelbrot(t_mlx *mlx);

void draw_line_to_image(t_mlx *e, int x, int x1, int y, int y1, int color);

void drawSierpinski(t_mlx *mlx, float x1, float y1, float x2, float y2, float x3, float y3);

void pixel_put_to_image(t_mlx *e, ulong img_color, int x, int y);

void ft_add_infos(t_mlx *mlx);

int ft_gere_expose(t_mlx *mlx);

int handle_mouse_button(int button, int x, int y, t_mlx *mlx);

int handle_mouse_motion(int x, int y, t_mlx *mlx);

int key_hook(int keycode, t_mlx *mlx);

#endif
