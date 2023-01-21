/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:09:48 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/17 19:50:15 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <math.h>
#include <errno.h>

#include "ft_obj_cone.h"
#include "ft_obj_base.h"

#include "ft_tool.h"

#include <stdio.h>
t_obj_cone	*ft_obj_cone_set()
{
	t_obj_cone *obj_cone;

	if (!ft_zeromalloc((void **)&obj_cone, sizeof(t_obj_cone)))
		ft_exit_print_error(ENOMEM, "ft_obj_cone_set()");
	obj_cone->base_color = ft_vector_3(0.0, 0.0, 0.0);
	obj_cone->gt = ft_gt_default();
	return (obj_cone);
}


bool	ft_obj_cone_intersection(t_obj_cone *obj_cone, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color)
{
	t_ray	back_ray = ft_gt_apply(&obj_cone->gt, cast_ray, &obj_cone->gt.back_to_form);

	t_vec3 v = ft_vec3_normalize(back_ray.lab);

	t_vec3 p = back_ray.point1;

	double	a = pow(v.x, 2.0) + pow(v.y, 2.0) - pow(v.z, 2.0);
	double	b = 2.0 * (p.x * v.x + p.y * v.y - p.z * v.z);
	double	c = pow(p.x, 2.0) + pow(p.y, 2.0) - pow(p.z, 2.0);
	

	double num_sqrt;
	
	num_sqrt = sqrt(pow(b, 2.0) - 4.0 * a * c);

	t_vec3	point[3];
	double	t[3];
	bool	t_valid[3];

	ft_memset(point, 0, sizeof(t_vec3 [3]));
	ft_memset(t, 0, sizeof(double [3]));
	t[0] = 100e6;
	t[1] = 100e6;
	t[2] = 100e6;
	ft_memset(t_valid, 0, sizeof(bool [3]));
	if (num_sqrt > 0.0)
	{
		t[0] = (-b + num_sqrt) / (2.0 * a);
		t[1] = (-b - num_sqrt) / (2.0 * a);

		point[0] = ft_vec3_add(back_ray.point1, ft_vec3_mult(v, t[0]));
		point[1] = ft_vec3_add(back_ray.point1, ft_vec3_mult(v, t[1]));

		if (t[0] > 0.0 && point[0].z > 0.0 && point[0].z < 1.0)
		{
			t_valid[0] = true;
		}
		else
		{
			t_valid[0] = false;
			t[0] = 100e6;
		}

		if (t[1] > 0.0 && point[1].z > 0.0 && point[1].z < 1.0)
			t_valid[1] = true;
		else
		{
			t_valid[1] = false;
			t[1] = 100e6;
		}
	}
	else
	{
		t_valid[0] = false;
		t_valid[1] = false;
		t[0] = 100e6;
		t[1] = 100e6;
	}

	if (ft_obj_close_enough(v.z, 0.0))
	{
		t_valid[2] = false;
		t[2] = 100e6;
	}
	else
	{
		t[2] = (back_ray.point1.z - 1.0) / - v.z;

		point[2] = ft_vec3_add(back_ray.point1, ft_vec3_mult(v, t[2]));
		
		if (t[2] > 0.0 && sqrt(pow(point[2].x, 2.0) + pow(point[2].y, 2.0)) < 1.0 )
		{
			t_valid[2] = true;
		}
		else
		{
			t_valid[2] = false;
			t[2] = 100e6;
		}
	}
	if (!t_valid[0] && !t_valid[1] && !t_valid[2])
		return false;
	
	int min_index = 9;
	double min_value = 10e6;
	int i;
	i = 0;
	while (i < 3)
	{
		if (t[i] < min_value)
		{
			min_value = t[i];
			min_index = i;
		}
		i++;
	}
	
	t_vec3	valid_point = point[min_index];
	t_vec3	org_normal = ft_vector_3(0.0, 0.0, 0.0);
	t_vec3	new_normal = ft_vector_3(0.0, 0.0, 0.0);
	t_vec3	local_origin = ft_vector_3(0.0, 0.0, 0.0);
	t_vec3	global_origin = ft_vector_3(0.0, 0.0, 0.0);
	t_vec3	normal_vector = ft_vector_3(0.0, 0.0, 0.0);
	
	if (min_index < 2)
	{
		*int_point = ft_gt_apply_vec3(&obj_cone->gt, &valid_point, &obj_cone->gt.forward_to_form);

		org_normal = ft_vector_3(0.0, 0.0, 0.0);
		new_normal = ft_vector_3(0.0, 0.0, 0.0);
		local_origin = ft_vector_3(0.0, 0.0, 0.0);
		global_origin = ft_gt_apply_vec3(&obj_cone->gt, &local_origin, &obj_cone->gt.forward_to_form);
		
		org_normal.x = valid_point.x;
		org_normal.y = valid_point.y;
		org_normal.z = -sqrt(pow(valid_point.x, 2.0) + pow(valid_point.y, 2.0));

		new_normal = ft_vec3_sub(ft_gt_apply_vec3(&obj_cone->gt, &org_normal, &obj_cone->gt.forward_to_form), global_origin);
		new_normal = ft_vec3_normalize(new_normal);

		*local_normal = new_normal;

		*local_color = obj_cone->base_color;

		return (true);
	}
	else
	{
		if (!ft_obj_close_enough(v.z, 0.0))
		{
			if (sqrt(pow(valid_point.x, 2.0) + pow(valid_point.y, 2.0) < 1.0))
			{
				*int_point = ft_gt_apply_vec3(&obj_cone->gt, &valid_point, &obj_cone->gt.forward_to_form);
						
				local_origin = ft_vector_3(0.0, 0.0, 0.0);
				normal_vector = ft_vector_3(0.0, 0.0, 1.0);
				global_origin = ft_gt_apply_vec3(&obj_cone->gt, &local_origin, &obj_cone->gt.forward_to_form);
				*local_normal = ft_vec3_normalize(ft_vec3_sub(ft_gt_apply_vec3(&obj_cone->gt, &normal_vector, &obj_cone->gt.forward_to_form), global_origin));
				
				*local_color = obj_cone->base_color;

				return (true);
			}
		}
	}
	return (false);
}