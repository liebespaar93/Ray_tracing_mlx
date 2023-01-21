/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:25:33 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/15 11:36:40 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <math.h>
#include <errno.h>

#include "ft_obj_base.h"
#include "ft_obj_plane.h"

#include "ft_tool.h"

#include <stdio.h>

t_obj_plane	*ft_obj_plane_set()
{
	t_obj_plane *obj_plane;

	if (!ft_zeromalloc((void **)&obj_plane, sizeof(t_obj_plane)))
		ft_exit_print_error(ENOMEM, "ft_obj_plane_set()");

	obj_plane->base_color = ft_vector_3(0.0, 0.0, 0.0);
	obj_plane->gt = ft_gt_default();
	return (obj_plane);
}

bool	ft_obj_plane_intersection(t_obj_plane *obj_plane, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color)
{
	t_ray	back_ray;

	back_ray = ft_gt_apply(&obj_plane->gt, cast_ray, &obj_plane->gt.back_to_form);

	t_vec3	k;
	k = ft_vec3_normalize(back_ray.lab);

	double	t;
	double	u;
	double	v;
	t_vec3	point;

	t_vec3	local_origin;
	t_vec3	normal_vector;
	t_vec3	global_origin;
	
	
	if (!ft_obj_close_enough(k.z, 0.0))
	{
		t = back_ray.point1.z / -k.z;
		if (t > 0.0)
		{
			u = back_ray.point1.x + (k.x * t);
			v = back_ray.point1.y + (k.y * t);

			if (fabs(u) < 1.0 && fabs(v) < 1.0)
			{
				point = ft_vec3_add(back_ray.point1, ft_vec3_mult(k, t));

				*int_point = ft_gt_apply_vec3(&obj_plane->gt, &point, &obj_plane->gt.forward_to_form);

				local_origin = ft_vector_3(0.0, 0.0, 0.0);
				normal_vector= ft_vector_3(0.0, 0.0, -1.0);
				global_origin = ft_gt_apply_vec3(&obj_plane->gt, &local_origin, &obj_plane->gt.forward_to_form);
				*local_normal = ft_vec3_sub(ft_gt_apply_vec3(&obj_plane->gt, &normal_vector, &obj_plane->gt.forward_to_form), global_origin);
				*local_normal = ft_vec3_normalize(*local_normal);

				*local_color = obj_plane->base_color;

				return (true);
			}
			else
				return (false);
		}
		else
			return (false);
	}
	else
		return (false);
}
