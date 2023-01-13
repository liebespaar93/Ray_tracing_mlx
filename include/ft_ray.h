/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:22:58 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 11:55:20 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RAY_H
# define FT_RAY_H

# include "ft_vector.h"

typedef	struct s_ray
{
	/* data */
	t_vec3	point1;
	t_vec3	point2;
	t_vec3	lab;
}	t_ray;

t_ray	ft_ray_defualt();
t_ray	ft_ray_set(const t_vec3 point1, const t_vec3 point2);

#endif
