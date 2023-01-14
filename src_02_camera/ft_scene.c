/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:52:16 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/14 12:02:42 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "ft_scene.h"
#include "ft_tool.h"
#include "ft_obj_base.h"

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

	t_obj_base	*obj_currnet;
	


	t_light_base	*light_currnet;
	double intensity;
	t_vec3	color;
	bool	valid_illum;

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
			obj_currnet = scene->obj_list;
			while (obj_currnet)
			{
				validint = ft_obj_sphere_intersection(&camera_ray, &int_point, &local_normal, &local_color);

				if (validint)
				{
					intensity = 0.0;
					color = ft_vector_3(0.0, 0.0, 0.0);
					valid_illum = false;
					light_currnet = scene->light_list;
					while (light_currnet)
					{
						valid_illum = ft_light_illumination(light_currnet, &int_point, &local_normal, scene->obj_list, obj_currnet, &color, &intensity);
						light_currnet = light_currnet->next;
					}

					dist = ft_vec3_norm(ft_vec3_sub(int_point, camera_ray.point1));
					if (dist > maxdist)
						maxdist = dist;
					if (dist < mindist)
						mindist = dist;

					if (valid_illum)
						ft_image_set_pixel(image, x, y, (const double [3]){255 * intensity, 0.0, 0.0});
					else
						ft_image_set_pixel(image, x, y, (const double [3]){0.0, 0.0, 0.0});
					
				}
				else
					ft_image_set_pixel(image, x, y, (const double [3]){0.0, 0.0, 0.0});
				obj_currnet = obj_currnet->next;
			}
			x++;
		}
		y++;
	}
	printf("maxdist : %f\n ", maxdist);
	printf("mindist : %f\n ", mindist);
	fflush(stdout);
	return (1);
}


