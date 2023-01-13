/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:52:16 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 16:50:07 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "ft_scene.h"
#include "ft_tool.h"

#include <stdio.h>

t_scene	*ft_scene_init()
{
	t_scene	*scene;

	if (!ft_zeromalloc((void **)&scene, sizeof(t_scene)))
		ft_exit_print_error(ENOMEM, "ft_scene_init()");
	
	scene->camera = ft_camera_init();
	scene->camera->position = ft_vector_3(0.0, -10.0, 0.0);
	scene->camera->look_at = ft_vector_3(0.0, 0.0, 0.0);
	scene->camera->up = ft_vector_3(0.0, 0.0, 1.0);
	scene->camera->horzsize = 0.25;
	scene->camera->aspect_ratio = 16.0 / 9.0;
	ft_camera_update_geometry(scene->camera);
	
	return (scene);
}


bool	ft_scene_render(t_scene *scene, t_image *image)
{
	int x;
	int y;

	t_ray	camera_ray = ft_ray_defualt();
	t_vec3	int_point = ft_vector_3(0.0, 0.0, 0.0);
	t_vec3	local_normal = ft_vector_3(0.0, 0.0, 0.0);
	t_vec3	local_color = ft_vector_3(0.0, 0.0, 0.0);

	double	xfact = 1.0 / ((double)image->x_size / 2.0);
	double	yfact = 1.0 / ((double)image->y_size / 2.0);
	double	mindist = 1e6;
	double	maxdist = 0.0;

	double normx;
	double normy;

	bool validint;
	

	double	dist;
	x = 0;
	y = 0;
	while (y < image->y_size)
	{
		x = 0;
		while (x < image->x_size)
		{
			normx = (double)x * xfact - 1.0;
			normy = (double)y * yfact - 1.0;

			ft_camera_generate_ray(scene->camera, normx, normy, &camera_ray);
			validint = ft_objsphere_intersection(&camera_ray, &int_point, &local_normal, &local_color);

			if (validint)
			{
				dist = ft_vec3_norm(ft_vec3_sub(int_point, camera_ray.point1));
				if (dist > maxdist)
					maxdist = dist;
				if (dist < mindist)
					mindist = dist;
				ft_image_set_pixel(image, x, y, (const double [3]){255 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0});
			}
			else
				ft_image_set_pixel(image, x, y, (const double [3]){0.0, 0.0, 0.0});
			x++;
		}
		y++;
	}
	printf("maxdist : %f\n ", maxdist);
	printf("mindist : %f\n ", mindist);
	fflush(stdout);
	return (1);
}


