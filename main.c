/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:28:42 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/12 15:35:07 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_app.h"
#include "mlx.h"
#include "ft_tool.h"

#include <stdio.h>
void ft_test_camera()
{
	t_camera c;

	c = ft_camera_init();
	c.position = ft_vector_3(0.0, 0.0, 0.0);
	c.look_at = ft_vector_3(0.0, 2.0, 0.0);
	c.up = ft_vector_3(0.0, 0.0, 1.0);
	c.length = 1.0;
	c.horzsize = 1.0;
	c.aspect_ratio = 1.0;
	ft_camera_update_geometry(&c);
	t_vec3 screen_center = c.screen_center;
	t_vec3 screen_u = c.screen_u;
	t_vec3 screen_v = c.screen_v;
	
	printf("Camera screen center: %f %f %f\n", screen_center.x, screen_center.y, screen_center.z);
	printf("Camera screen u     : %f %f %f\n", screen_u.x, screen_u.y, screen_u.z);
	printf("Camera screen v     : %f %f %f\n", screen_v.x, screen_v.y, screen_v.z);
}

int main(int argc, char const *argv[])
{
	t_app	*app;
	
	/* code */
	(void)argc;
	(void)argv;
	app = ft_app_init();
	ft_test_camera();
	ft_app_execute(app);
	system("leaks a.out");
	(void)app;
	return 0;
}
