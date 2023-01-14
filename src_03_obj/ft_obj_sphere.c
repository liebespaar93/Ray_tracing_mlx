/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:17 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/14 22:47:10 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <errno.h>

#include "ft_obj_sphere.h"
#include <stdio.h>

#include "ft_tool.h"

t_obj_sphere	*ft_obj_sphere_set()
{
	t_obj_sphere *obj_sphere;

	if (!ft_zeromalloc((void **)&obj_sphere, sizeof(t_obj_sphere)))
		ft_exit_print_error(ENOMEM, "ft_obj_sphere_set()");
	obj_sphere->base_color = ft_vector_3(0.0, 0.0, 0.0);
	obj_sphere->gt = ft_gt_default();
	return (obj_sphere);
}

bool	ft_obj_sphere_intersection(t_obj_sphere *obj_sphere, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color)
{
	t_ray	back_ray = ft_gt_apply(&obj_sphere->gt, cast_ray, &obj_sphere->gt.back_to_form);
	
	t_vec3 vhat;
	double b;
	double c;
	double int_test;

	vhat = ft_vec3_normalize(back_ray.lab);

	b = 2.0 * ft_vec3_dot(back_ray.point1, vhat);
	c = ft_vec3_dot(back_ray.point1, back_ray.point1) - 1.0;

	int_test = (b * b) - (4.0 * c);

	t_vec3 point;
	double num_sqrt;
	double t1;
	double t2;
	
	if (int_test > 0.0)
	{
		num_sqrt = sqrt(int_test);
		t1 = (-b + num_sqrt) / 2.0;
		t2 = (-b - num_sqrt) / 2.0;
		if ( (t1 < 0.0) || (t2 < 0.0))
			return false;
		if (t1 < t2)
			point = ft_vec3_add(back_ray.point1, ft_vec3_mult(vhat, t1));
		else
			point = ft_vec3_add(back_ray.point1, ft_vec3_mult(vhat, t2));


		*int_point = ft_gt_apply_vec3(&obj_sphere->gt, &point, &obj_sphere->gt.forward_to_form);

		t_vec3 obj_origin = ft_vector_3(0.0, 0.0, 0.0);
		t_vec3 new_obj_origin = ft_gt_apply_vec3(&obj_sphere->gt, &obj_origin, &obj_sphere->gt.forward_to_form);
		
		*local_normal = ft_vec3_sub(*int_point, new_obj_origin);
		*local_normal = ft_vec3_normalize(*local_normal);
		
		*local_color = obj_sphere->base_color;
		return true;
	}
	return false;
	
}
