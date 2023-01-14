/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_sphere.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:06:50 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/14 21:44:03 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJSPHERE_H
# define FT_OBJSPHERE_H

#include <stdbool.h>
#include "ft_ray.h"
# include "ft_geometric_transform.h"

typedef struct s_obj_sphere
{
	/* data */
	t_vec3	base_color;
	t_gt	gt;
}	t_obj_sphere;


t_obj_sphere	*ft_obj_sphere_set();
bool			ft_obj_sphere_intersection(t_obj_sphere *obj_sphere, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color);

#endif
