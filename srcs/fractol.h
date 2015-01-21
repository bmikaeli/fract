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

# define BUFF_SIZE	1024
# define WIDTH 1000
# define HEIGHT 1000
# define N 30
typedef unsigned long	ulong;

# define ECHAP    65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
typedef struct	s_color
{
    int	r;
    int	g;
    int	b;
} t_color;


# include "libft.h"
# include <mlx.h>

typedef struct	s_mlx
{
    void	*mlx_ptr;
    void	*win_ptr;
    void	*img_ptr;
    char	*img;
    int	    bpp;
    int	    size_line;
    int	    endian;
    float   Cb;
    float   Ca;
} t_mlx;


#endif
