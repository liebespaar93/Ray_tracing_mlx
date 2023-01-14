/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:28:42 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/14 12:05:44 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_app.h"
#include "mlx.h"
#include "ft_tool.h"

#include <stdio.h>

void	ft_test_light(t_app *app)
{
	app->scene->light_list = ft_light_base_pushback(&app->scene->light_list, "light_point", ft_light_point_set());
	ft_light_location_set(app->scene->light_list, ft_vector_3(5.0, -10.0, -5.0));
	ft_light_color_set(app->scene->light_list, ft_vector_3(255.0, 255.0, 255.0));
}

int main(int argc, char const *argv[])
{
	t_app	*app;
	
	/* code */
	(void)argc;
	(void)argv;
	app = ft_app_init();
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "sphere", ft_obj_sphere_set());
	ft_test_light(app);
	ft_app_execute(app);
	system("leaks a.out");
	(void)app;
	return 0;
}
