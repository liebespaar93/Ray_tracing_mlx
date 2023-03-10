/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:31 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 11:52:29 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ray.h"

t_ray	ft_ray_defualt()
{
	t_ray ray;

	ray.point1 = ft_vector_3(0.0, 0.0, 0.0);
	ray.point2 = ft_vector_3(0.0, 0.0, 1.0);
	ray.lab = ft_vec3_sub(ray.point2, ray.point1);
	return (ray);
}

t_ray	ft_ray_set(const t_vec3 point1, const t_vec3 point2)
{
	t_ray ray;
	
	ray.point1 = point1;
	ray.point2 = point2;
	ray.lab = ft_vec3_sub(point2, point1);

	return (ray);
}