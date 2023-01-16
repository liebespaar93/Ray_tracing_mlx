/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_material_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:54:22 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/16 15:43:16 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "ft_material_base.h"
#include "ft_tool.h"

t_material_base *ft_materia_base_set(char *type, void *material)
{
	t_material_base	*material_base;

	if (!ft_zeromalloc((void **)&material_base, sizeof(t_material_base)))
		ft_exit_print_error(ENOMEM, "ft_materia_base_set()");
	material_base->type = type;
	material_base->material = material;
	material_base->max_reflection_rays = 5;
	material_base->reflection_ray_count = 0;
	return (material_base);
}

bool ft_materia_base_set_color(t_material_base *materia_base, t_vec3 base_color)
{
	if (!ft_strcmp(materia_base->type, "simple"))
		((t_material_simple *)materia_base->material)->base_color = base_color;
	else
		return (false);
	return (true);
}

bool ft_materia_base_set_reflectivity(t_material_base *materia_base, double reflectivity)
{
	if (!ft_strcmp(materia_base->type, "simple"))
		((t_material_simple *)materia_base->material)->reflectivity = reflectivity;
	else
		return (false);
	return (true);
}

bool ft_materia_base_set_shininess(t_material_base *materia_base, double shininess)
{
	if (!ft_strcmp(materia_base->type, "simple"))
		((t_material_simple *)materia_base->material)->shininess = shininess;
	else
		return (false);
	return (true);
}

t_vec3	ft_material_base_compute_color(t_material_base *materia_base, t_obj_base *obj_list, t_light_base *light_list, t_obj_base *current_obj,
	t_vec3 *int_point, t_vec3 *local_normal, t_ray *camera_ray)
{
	t_vec3	color;

	color = ft_vector_3(0.0, 0.0, 0.0);
	if (!ft_strcmp(materia_base->type, "simple"))
		color = ft_material_simple_compute_color(materia_base, (t_material_simple *)materia_base->material, obj_list, light_list, current_obj, int_point,local_normal, camera_ray);
		
	return (color);
}

t_vec3	ft_material_base_diffuse_color(t_obj_base *obj_list, t_light_base *light_list, t_obj_base *current_obj,
	t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *base_color)
{
	t_light_base	*currnt_light;
	t_vec3	diffuse_color;
	t_vec3	color;
	double	red;
	double	green;
	double	blue;
	double	intensity;
	bool	valid_illum;
	bool	illum_found;

	diffuse_color = ft_vector_3(0.0, 0.0, 0.0);
	color = ft_vector_3(0.0, 0.0, 0.0);
	intensity = 0.0;
	red = 0.0;
	green = 0.0;
	blue = 0.0;
	intensity = 0.0;
	valid_illum = false;
	illum_found = false;

	currnt_light = light_list;
	while (currnt_light)
	{
		valid_illum = ft_light_illumination(currnt_light, int_point,local_normal, obj_list, current_obj, &color, &intensity);
		if (valid_illum)
		{
			illum_found = true;
			red += color.x * intensity;
			green += color.y * intensity;
			blue += color.z * intensity;
		}
		currnt_light = currnt_light->next;
	}

	if (illum_found)
	{
		diffuse_color.x = red * base_color->x;
		diffuse_color.y = green * base_color->y;
		diffuse_color.z = blue * base_color->z;
	}
	return (diffuse_color);
}


t_vec3	ft_material_base_compute_reflection_color(t_material_base *material_base, t_obj_base *obj_list, t_light_base *light_list, t_obj_base *current_obj,
	t_vec3 *int_point, t_vec3 *local_normal, t_ray *incident_ray)
{
	t_vec3		reflection_color;
	t_vec3		d;
	t_vec3		reflection_vec;
	t_ray		reflection_ray;

	t_obj_base *closest_obj;
	t_vec3	closest_int_point;
	t_vec3	closest_local_normal;
	t_vec3	closest_local_color;
	bool intersection_found;

	reflection_color = ft_vector_3(0.0, 0.0, 0.0);
	d = incident_ray->lab;
	reflection_vec = ft_vec3_sub(d, ft_vec3_mult(*local_normal ,ft_vec3_dot(*local_normal, d) * 2));

	reflection_ray = ft_ray_set(*int_point, ft_vec3_add(*int_point, reflection_vec));

	closest_obj = NULL;
	closest_int_point = ft_vector_3(0.0, 0.0, 0.0);
	closest_local_normal = ft_vector_3(0.0, 0.0, 0.0);
	closest_local_color = ft_vector_3(0.0, 0.0, 0.0);
	intersection_found = ft_material_base_cast_ray(&reflection_ray, obj_list, current_obj, \
		&closest_obj, &closest_int_point, &closest_local_normal, &closest_local_color);

	t_vec3	mat_color;
	mat_color = ft_vector_3(0.0, 0.0, 0.0);
	
	if (intersection_found && material_base->reflection_ray_count < material_base->max_reflection_rays)
	{
		material_base->reflection_ray_count++;

		if (closest_obj->material)
		{
			closest_obj->material->reflection_ray_count = 0;
			mat_color = ft_material_base_compute_color(closest_obj->material, obj_list, light_list, \
				closest_obj, &closest_int_point, &closest_local_normal, &reflection_ray);
		}
		else
		{
			mat_color = ft_material_base_diffuse_color(obj_list, light_list, \
				closest_obj, &closest_int_point, &closest_local_normal, ft_obj_base_get_color(closest_obj));
		}
	}
	else
	{

	}
	reflection_color = mat_color;
	return (reflection_color);
}

bool	ft_material_base_cast_ray(t_ray *cast_ray, t_obj_base *obj_list, t_obj_base *this_obj, \
	t_obj_base **closest_obj, t_vec3 *closest_int_point, t_vec3 *closest_local_normal, t_vec3 *closest_local_color)
{
	t_vec3	int_point;
	t_vec3	local_normal;
	t_vec3	local_color;

	int_point = ft_vector_3(0.0, 0.0, 0.0);
	local_normal = ft_vector_3(0.0, 0.0, 0.0);
	local_color = ft_vector_3(0.0, 0.0, 0.0);
	
	double	dist;
	double	min_dist = 1e6;
	bool	intersction_found = false;

	t_obj_base	*current_obj;

	bool valid_int;

	current_obj = obj_list;
	while (current_obj)
	{
		if (current_obj != this_obj)
		{
			valid_int = ft_obj_base_intersection(current_obj, cast_ray, &int_point, &local_normal, &local_color);
			if (valid_int)
			{

				intersction_found = true;
				dist = ft_vec3_norm(ft_vec3_sub(int_point, cast_ray->point1));
				
				if (dist < min_dist)
				{
					min_dist = dist;
					*closest_obj = current_obj;
					*closest_int_point = int_point;
					*closest_local_normal = local_normal;
					*closest_local_color = local_color;
				}
			}
		}
		current_obj = current_obj->next;
	}
	return (intersction_found);
}

