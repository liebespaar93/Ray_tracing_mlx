/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:52:16 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/15 12:33:42 by kyoulee          ###   ########.fr       */
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
	double	min_dist = 1e6;
	double	max_dist = 0.0;

	double normx;
	double normy;

	bool validint;
	

	double	dist;

	t_obj_base	*obj_currnet;
	


	t_light_base	*light_currnet;
	double intensity;
	t_vec3	color;
	bool	valid_illum;
	bool	illum_found;


	t_obj_base	*close_obj;
	t_vec3	close_int_point;
	t_vec3	close_local_normal;
	t_vec3	close_local_color;
	bool	intersection_found;

	double red;
	double green;
	double blue;

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
			close_obj = NULL;
			close_int_point = ft_vector_3(0.0, 0.0, 0.0);
			close_local_normal = ft_vector_3(0.0, 0.0, 0.0);
			close_local_color = ft_vector_3(0.0, 0.0, 0.0);

			min_dist = 1e6;
			intersection_found = false;
			while (obj_currnet)
			{
				validint = ft_obj_base_intersection(obj_currnet, &camera_ray, &int_point, &local_normal, &local_color);

				if (validint)
				{
					intersection_found = true;

					dist = ft_vec3_norm(ft_vec3_sub(int_point, camera_ray.point1));

					if (dist < min_dist)
					{
						min_dist = dist;
						close_obj = obj_currnet;
						close_int_point = int_point;
						close_local_normal = local_normal;
						close_local_color = local_color;
					}
				}
				obj_currnet = obj_currnet->next;
			}
			if (intersection_found)
			{
				intensity = 0.0;
				color = ft_vector_3(0.0, 0.0, 0.0);
				red = 0.0;
				green = 0.0;
				blue = 0.0;
				valid_illum = false;
				illum_found = false;
				light_currnet = scene->light_list;
				while (light_currnet)
				{
					valid_illum = ft_light_illumination(light_currnet, &close_int_point, &close_local_normal, scene->obj_list, close_obj, &color, &intensity);

					if (valid_illum)
					{
						illum_found = true;
						red += color.x * intensity;
						green += color.y * intensity;
						blue += color.z * intensity;
					}
					light_currnet = light_currnet->next;
				}
			}

			if (illum_found)
			{
				red *= close_local_color.x;
				green *= close_local_color.y;
				blue *= close_local_color.z;
				ft_image_set_pixel(image, x, y, (double [3]){red, green, blue});
			}
			x++;
		}
		y++;
	}
	printf("maxdist : %f\n ", max_dist);
	printf("mindist : %f\n ", min_dist);
	fflush(stdout);
	return (1);
}


