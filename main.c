/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:28:42 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/12 13:35:58 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_app.h"
#include "mlx.h"
#include "ft_tool.h"

void ft_test_ray(t_app *app)
{
	double x, y;
	double r, g;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			r = (x / SCREEN_WIDTH) * 255.0;
			g = (y / SCREEN_HEIGHT) * 255.0;
			ft_image_set_pixel(app->image, x, y, (const double [3]){r, g, 0.0});
			x++;
		}
		y++;
	}

}

int main(int argc, char const *argv[])
{
	t_app	*app;
	
	/* code */
	(void)argc;
	(void)argv;
	app = ft_app_init();
	ft_test_ray(app);
	ft_app_execute(app);
	system("leaks a.out");
	return 0;
}
