/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:52:16 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/16 15:43:51 by kyoulee          ###   ########.fr       */
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
	return (scene);
}


bool	ft_scene_render(t_scene *scene, t_image *image)
{
	int x;
	int y;

	t_ray	camera_ray = ft_ray_defualt();

	double	xfact = 1.0 / ((double)image->x_size / 2.0);
	double	yfact = 1.0 / ((double)image->y_size / 2.0);

	double normx;
	double normy;

	t_vec3	color;


	t_obj_base	*close_obj;
	t_vec3	close_int_point;
	t_vec3	close_local_normal;
	t_vec3	close_local_color;
	bool	intersection_found;

	close_obj = NULL;
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
			intersection_found = ft_scene_cast_ray(scene, &camera_ray, &close_obj, &close_int_point, &close_local_normal, &close_local_color);
			
			if (intersection_found)
			{
				if (close_obj->material)
				{
					close_obj->material->reflection_ray_count = 0;
					color = ft_material_base_compute_color(close_obj->material, scene->obj_list, scene->light_list, close_obj, &close_int_point, &close_local_normal, &camera_ray);
					ft_image_set_pixel(image, x, y, (double [3]){color.x, color.y, color.z});
				}
				else
				{
					color = ft_material_base_diffuse_color(scene->obj_list, scene->light_list, close_obj, &close_int_point, &close_local_normal, ft_obj_base_get_color(close_obj));
					ft_image_set_pixel(image, x, y, (double [3]){color.x, color.y, color.z});
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	ft_scene_cast_ray(t_scene *scene, t_ray *cast_ray, 
	t_obj_base **close_obj, t_vec3 *close_int_point, t_vec3 *close_local_normal, t_vec3 *close_local_color)
{
	t_obj_base	*obj_currnet;
	t_vec3	int_point = ft_vector_3(0.0, 0.0, 0.0);
	t_vec3	local_normal = ft_vector_3(0.0, 0.0, 0.0);
	t_vec3	local_color = ft_vector_3(0.0, 0.0, 0.0);
	
	double	dist;
	double	min_dist;
	
	bool	intersection_found;
	bool 	validint;

	min_dist = 1e6;
	intersection_found = false;
	
	obj_currnet = scene->obj_list;
	while (obj_currnet)
	{
		validint = ft_obj_base_intersection(obj_currnet, cast_ray, &int_point, &local_normal, &local_color);

		if (validint)
		{
			intersection_found = true;

			dist = ft_vec3_norm(ft_vec3_sub(int_point, cast_ray->point1));

			if (dist < min_dist)
			{
				min_dist = dist;
				*close_obj = obj_currnet;
				*close_int_point = int_point;
				*close_local_normal = local_normal;
				*close_local_color = local_color;
			}
		}
		obj_currnet = obj_currnet->next;
	}
	return (intersection_found);
}