/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_material_simple.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:23:26 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/16 15:29:51 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <errno.h>

#include "ft_material_simple.h"
#include "ft_tool.h"

t_material_simple	*ft_material_simple_default()
{
	t_material_simple	*material_simple;

	if (!ft_zeromalloc((void **)&material_simple, sizeof(t_material_simple)))
		ft_exit_print_error(ENOMEM, "ft_material_simple_default()");
	
	material_simple->base_color = ft_vector_3(0.0, 0.0, 0.0);
	material_simple->reflectivity = 0.0;
	material_simple->shininess = 0.0;

	return (material_simple);
}

t_vec3	ft_material_simple_compute_color(t_material_base *material_base, t_material_simple *material_simple, t_obj_base *obj_list, t_light_base *light_list, t_obj_base *current_obj,
	t_vec3 *int_point, t_vec3 *local_normal, t_ray *camera_ray)
{
	t_vec3	mat_color;
	t_vec3	ref_color;
	t_vec3	dif_color;
	t_vec3	spc_color;

	mat_color = ft_vector_3(0.0, 0.0, 0.0);
	ref_color = ft_vector_3(0.0, 0.0, 0.0);
	dif_color = ft_vector_3(0.0, 0.0, 0.0);
	spc_color = ft_vector_3(0.0, 0.0, 0.0);

	dif_color = ft_material_base_diffuse_color(obj_list, light_list, current_obj, int_point, local_normal, &material_simple->base_color);

	if (material_simple->reflectivity > 0.0)
	{
		ref_color = ft_material_base_compute_reflection_color(material_base, obj_list, light_list, current_obj, int_point, local_normal, camera_ray);
	}
	
	mat_color = ft_vec3_add(ft_vec3_mult(ref_color, material_simple->reflectivity), ft_vec3_mult(dif_color, 1 - material_simple->reflectivity));

	if (material_simple->shininess > 0.0)
		spc_color = ft_material_simple_compute_specular(material_simple, obj_list, light_list, int_point, local_normal, camera_ray);

	mat_color = ft_vec3_add(mat_color, spc_color);

	return (mat_color);
}

t_vec3	ft_material_simple_compute_specular(t_material_simple *material_simple, t_obj_base *obj_list, t_light_base *light_list,
	t_vec3 *int_point, t_vec3 *local_normal, t_ray *camera_ray)
{
	t_light_base	*current_light;
	t_obj_base	*scene_obj;

	double	intensity;
	t_vec3	*location;
	t_vec3	light_dir;
	t_vec3	start_point;

	t_ray	light_ray;

	t_vec3	point;
	t_vec3	point_normal;
	t_vec3	point_color;

	bool	valid_int;

	t_vec3	d;
	t_vec3	r;
	t_vec3	v;

	double dot_product;

	t_vec3	*color;
	
	t_vec3 spc_color = ft_vector_3(0.0, 0.0, 0.0);
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;


	current_light = light_list;
	while (current_light)
	{
		intensity = 0.0;
		
		location = ft_light_location_get(current_light);
		
		light_dir = ft_vec3_normalize(ft_vec3_sub(*location, *int_point));
		
		start_point = ft_vec3_sub(*int_point, ft_vec3_mult(light_dir, 0.001));

		light_ray = ft_ray_set(start_point, ft_vec3_add(start_point, light_dir));

		point = ft_vector_3(0.0, 0.0, 0.0);
		point_normal = ft_vector_3(0.0, 0.0, 0.0);
		point_color = ft_vector_3(0.0, 0.0, 0.0);
		valid_int = false;
		scene_obj = obj_list;
		while (scene_obj)
		{
			valid_int = ft_obj_base_intersection(scene_obj, &light_ray, &point, &point_normal, &point_color);
			if (valid_int)
				break;
			scene_obj = scene_obj->next;
		}

		if (!valid_int)
		{
			d = light_ray.lab;
			r = ft_vec3_sub(d, ft_vec3_mult(*local_normal, ft_vec3_dot(d, *local_normal) * 2));
			r = ft_vec3_normalize(r);

			v = ft_vec3_normalize(camera_ray->lab);
			
			dot_product = ft_vec3_dot(r,v);
			if (dot_product > 0.0)
			{
				intensity = material_simple->reflectivity * pow(dot_product, material_simple->shininess);
			}
		}
		color = ft_light_color_get(current_light);
		red += color->x * intensity;
		green += color->y * intensity;
		blue += color->z * intensity;
		
		current_light = current_light->next;
	}
	spc_color.x = red;
	spc_color.y = green;
	spc_color.z = blue;

	return (spc_color);
}

