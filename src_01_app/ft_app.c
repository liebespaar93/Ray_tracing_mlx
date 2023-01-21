/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 05:39:46 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 16:48:22 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "mlx.h"

#include "ft_app.h"
#include "ft_tool.h"

t_app	*ft_app_set()
{
	t_app	*app;

	if (!ft_zeromalloc((void **)&app, sizeof(t_app)) ||
		!ft_zeromalloc((void **)&app->mlx, sizeof(t_mlx)) ||
		!ft_zeromalloc((void **)&app->renderer, sizeof(t_renderer)))
		ft_exit_print_error(ENOMEM, "ft_app_set()");
	app->isrunning = true;
	app->mlx->mlx_ptr = mlx_init();
	if (!app->mlx->mlx_ptr)
		ft_exit_print_error(EFAULT, "mlx_init()");
	app->mlx->win_ptr = mlx_new_window(app->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "minirt 0.3v");
	if (!app->mlx->win_ptr)
		ft_exit_print_error(EFAULT, "mlx_new_window()");
	app->mlx->img_ptr = mlx_new_image(app->mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!app->mlx->img_ptr)
		ft_exit_print_error(EFAULT, "mlx_new_image()");
	app->renderer->buffer = mlx_get_data_addr(app->mlx->img_ptr, &app->renderer->bits_per_pixel, &app->renderer->size_line, &app->renderer->endian);
	if (!app->renderer->buffer)
		ft_exit_print_error(EFAULT, "mlx_get_data_addr()");
	
	return (app);
}

t_app	*ft_app_init()
{
	t_app	*app;

	app = ft_app_set();
	app->image = ft_image_init(SCREEN_WIDTH, SCREEN_HEIGHT);
	app->scene = ft_scene_init();
	return (app);
}

void	ft_app_render(t_app *app)
{
	ft_image_display(app->image, app->renderer->endian);
	ft_memcpy(app->renderer->buffer, app->image->temp_pixel, app->image->x_size * app->image->y_size * 4);
	mlx_put_image_to_window(app->mlx->mlx_ptr,app->mlx->win_ptr, app->mlx->img_ptr, 10, 10);
}

int	ft_app_event(t_app *app)
{
	if (!app)
		ft_exit_print_error(EFAULT, "ft_app_event()");
	ft_app_render(app);
	return (0);
}

void	ft_app_exit(t_app *app)
{
	if (app)
	{
		if (app->mlx->img_ptr)
			mlx_destroy_image(app->mlx->mlx_ptr, app->mlx->img_ptr);
		if (app->mlx->win_ptr)
			mlx_destroy_window(app->mlx->mlx_ptr, app->mlx->win_ptr);
		free(app);
	}
}

void	ft_app_execute(t_app *app)
{
	if (!app)
		ft_exit_print_error(EFAULT, "ft_app_execute()");

	ft_scene_render(app->scene, app->image);
	mlx_loop_hook(app->mlx->mlx_ptr, ft_app_event, (void *)app);
	mlx_loop(app->mlx->mlx_ptr);
}