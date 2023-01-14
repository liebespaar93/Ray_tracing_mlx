/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:17 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/14 11:58:55 by kyoulee          ###   ########.fr       */
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
	return (obj_sphere);
}

bool	ft_obj_sphere_intersection(t_ray *ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color)
{
	(void)int_point;
	(void)local_color;
	
	t_vec3 vhat;
	double b;
	double c;
	double int_test;

	vhat = ft_vec3_normalize(ray->lab);

	b = 2.0 * ft_vec3_dot(ray->point1, vhat);
	c = ft_vec3_dot(ray->point1, ray->point1) - 1.0;

	int_test = (b * b) - (4.0 * c);

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
			*int_point = ft_vec3_add(ray->point1, ft_vec3_mult(vhat, t1));
		else
			*int_point = ft_vec3_add(ray->point1, ft_vec3_mult(vhat, t2));
		*local_normal = *int_point;
		*local_normal = ft_vec3_normalize(*local_normal);
		

		return true;
	}
	return false;
	
}