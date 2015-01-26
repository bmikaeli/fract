/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <bmikaeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:21:26 by bmikaeli          #+#    #+#             */
/*   Updated: 2015/01/26 13:00:53 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			choose_fractal(t_mlx *mlx, char *name)
{
	if (!strcmp(name, "julia"))
		return (mlx->name = JULIA);
	else if (!strcmp(name, "mandelbrot"))
		return (mlx->name = MANDELBROT);
	else if (!strcmp(name, "pizza"))
		return (mlx->name = PIZZULIA);
	else
		ft_putendl("wrong parameter");
	return (0);
}

int			main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
	{
		ft_putendl("usage : ./fractol <Fractal_Name> (julia/mandelbrot/pizza)");
		return (0);
	}
	if ((mlx.ca = -0.4242) && !choose_fractal(&mlx, av[1]))
		return (0);
	mlx.mlx_ptr = mlx_init();
	mlx_do_key_autorepeaton(mlx.mlx_ptr);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Fract'Ol");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
	mlx.cb = +0.4242;
	mlx.iteration = 7;
	mlx.img_height = 1000;
	mlx.img_width = 1000;
	mlx.color_shift = 8;
	mlx.zoom = 4;
	mlx_mouse_hook(mlx.win_ptr, handle_mouse_button, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1, key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 6, (1L << 6), handle_mouse_motion, &mlx);
	mlx_expose_hook(mlx.win_ptr, ft_gere_expose, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
