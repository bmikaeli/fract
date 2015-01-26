/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <bmikaeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 12:22:36 by bmikaeli          #+#    #+#             */
/*   Updated: 2015/01/26 14:55:45 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			julia(t_mlx *mlx)
{
	t_complex	cx;

	cx.x = 0;
	while (++cx.x < mlx->img_height)
	{
		cx.y = 0;
		while (++cx.y < mlx->img_width)
		{
			cx.re = mlx->zoom * cx.x / WIDTH - (mlx->zoom / 2) + mlx->mouse_x;
			cx.im = -mlx->zoom * cx.y / HEIGHT + (mlx->zoom / 2) + mlx->mouse_y;
			cx.i = 0;
			while (++cx.i < mlx->iteration)
			{
				cx.temp = cx.re;
				cx.re = cx.re * cx.re - cx.im * cx.im + mlx->ca;
				cx.im = 2 * cx.temp * cx.im + mlx->cb;
				if (cx.re * cx.re + cx.im * cx.im > 4)
					break ;
			}
			cx.color = (255 - cx.i * 255) / mlx->iteration << mlx->color_shift;
			cx.color += (255 - cx.i * 255) / mlx->iteration;
			pixel_put_to_image(mlx, cx.color, cx.x, cx.y);
		}
	}
}

void			julia_pizza(t_mlx *mlx)
{
	t_complex	cx;

	cx.x = 0;
	while (++cx.x < mlx->img_height)
	{
		cx.y = 0;
		while (++cx.y < mlx->img_width)
		{
			cx.re = mlx->zoom * cx.x / WIDTH - (mlx->zoom / 2) + mlx->mouse_x;
			cx.im = -mlx->zoom * cx.y / HEIGHT + (mlx->zoom / 2) + mlx->mouse_y;
			cx.i = 0;
			while (++cx.i < mlx->iteration)
			{
				cx.temp = cx.re;
				cx.re = cx.re * cx.re - cx.im * cx.im + mlx->ca;
				cx.im = sin(2 * cx.temp * cx.im + mlx->cb);
				if (cx.re * cx.re + cx.im * cx.im > 4)
					break ;
			}
			cx.color = (255 - cx.i * 255) / mlx->iteration << mlx->color_shift;
			cx.color += (255 - cx.i * 255) / mlx->iteration;
			pixel_put_to_image(mlx, cx.color, cx.x, cx.y);
		}
	}
}

int				compute_mandelbrot(t_mlx *mlx, int x, int y)
{
	t_complex	cx;

	cx.pr = mlx->zoom * (float)x / WIDTH - (mlx->zoom / 2);
	cx.pi = -mlx->zoom * (float)y / HEIGHT + (mlx->zoom / 2);
	cx.newre = 0;
	cx.newim = 0;
	cx.i = 0;
	while (++cx.i < mlx->iteration)
	{
		cx.oldre = cx.newre;
		cx.oldim = cx.newim;
		cx.newre = cx.oldre * cx.oldre - cx.oldim * cx.oldim + cx.pr;
		cx.newim = 2 * cx.oldre * cx.oldim + cx.pi;
		if ((cx.newre * cx.newre + cx.newim * cx.newim) > 4)
			break ;
	}
	return (cx.i);
}

void			mandelbrot(t_mlx *mlx)
{
	int			color;
	int			y;
	int			x;
	int			i;

	x = 0;
	while (++x < mlx->img_height)
	{
		y = 0;
		while (++y < mlx->img_width)
		{
			i = compute_mandelbrot(mlx, x, y);
			color = (255 - i * 255) / mlx->iteration << mlx->color_shift;
			color += (255 - i * 255) / mlx->iteration;
			pixel_put_to_image(mlx, color, x, y);
		}
	}
}
