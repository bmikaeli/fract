/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <bmikaeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 12:09:27 by bmikaeli          #+#    #+#             */
/*   Updated: 2015/01/26 12:51:58 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put_to_image(t_mlx *e, t_ulong img_color, int x, int y)
{
	char	*data;
	uint	r;
	uint	g;
	uint	b;

	data = mlx_get_data_addr(e->img_ptr, &(e->bpp), &(e->size_line),
		&(e->endian));
	b = mlx_get_color_value(e->mlx_ptr, (img_color & 0xff));
	g = mlx_get_color_value(e->mlx_ptr, (img_color & 0xff00) >> 8);
	r = mlx_get_color_value(e->mlx_ptr, (img_color & 0xff0000) >> 16);
	*(data + y * e->size_line + (e->bpp / 8) * x) = b;
	*(data + y * e->size_line + (e->bpp / 8) * x + 1) = g;
	*(data + y * e->size_line + (e->bpp / 8) * x + 2) = r;
}

int		ft_gere_expose(t_mlx *mlx)
{
	if (mlx->name == JULIA)
		julia(mlx);
	if (mlx->name == MANDELBROT)
		mandelbrot(mlx);
	if (mlx->name == PIZZULIA)
		julia_pizza(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr,
		0, 0);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 20, 0xffffff, "zoom :");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 20, 0xffffff,
		ft_itoa(mlx->zoom));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 80, 20, 0xffffff,
		"iterations :");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 160, 20, 0xffffff,
		ft_itoa(mlx->iteration));
	return (0);
}

int		handle_mouse_motion(int x, int y, t_mlx *mlx)
{
	if (!mlx->lock)
	{
		if (x > mlx->last_x)
			mlx->cb += 0.01f;
		if (x < mlx->last_x)
			mlx->cb -= 0.01f;
		if (y > mlx->last_y)
			mlx->ca += 0.01f;
		if (y < mlx->last_y)
			mlx->ca -= 0.01f;
		mlx->last_x = x;
		mlx->last_y = y;
		ft_gere_expose(mlx);
	}
	return (0);
}

int		handle_mouse_button(int button, int x, int y, t_mlx *mlx)
{
	static int i = 0;

	if (button == 4 && mlx->zoom > 0 && (i % 3) == 0)
		mlx->zoom -= 0.25f;
	if (button == 5 && mlx->zoom < 5 && (i % 3) == 0)
		mlx->zoom += 0.25f;
	(void)y;
	(void)x;
	i++;
	ft_gere_expose(mlx);
	return (0);
}

int		key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 108)
		mlx->lock = mlx->lock ? 0 : 1;
	if (keycode == 99)
	{
		mlx->color_shift++;
		if (mlx->color_shift >= 12)
			mlx->color_shift = 4;
	}
	if (keycode == ECHAP)
		exit(1);
	if (keycode == UP)
		mlx->mouse_y += 0.03 / mlx->zoom;
	if (keycode == DOWN)
		mlx->mouse_y -= 0.03 / mlx->zoom;
	if (keycode == LEFT)
		mlx->mouse_x -= 0.03 / mlx->zoom;
	if (keycode == RIGHT)
		mlx->mouse_x += 0.03 / mlx->zoom;
	if (keycode == MINUS && mlx->iteration > 1)
		mlx->iteration -= 1;
	if (keycode == PLUS)
		mlx->iteration += 1;
	ft_gere_expose(mlx);
	return (0);
}
