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
    int N;
    int img_width;
    int img_height;
    int size_line;
    int endian;
    float Cb;
    float zoom;
    float Ca;
} t_mlx;
typedef unsigned long ulong;

void pixel_put_to_image(t_mlx *e, ulong img_color, int x, int y);

#endif
