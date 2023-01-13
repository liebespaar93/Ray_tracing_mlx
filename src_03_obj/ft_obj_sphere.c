/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:17 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 16:39:17 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ft_obj_sphere.h"
#include <stdio.h>

#include "ft_tool.h"

bool	ft_objsphere_intersection(t_ray *ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color)
{
	(void)int_point;
	(void)local_normal;
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
		{
			*int_point = ft_vec3_add(ray->point1, ft_vec3_mult(vhat, t1));

		}
		else
		{
			*int_point = ft_vec3_add(ray->point1, ft_vec3_mult(vhat, t2));
		}
		return true;
	}
	return false;
	
}