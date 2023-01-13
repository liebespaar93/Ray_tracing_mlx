/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_sphere.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:06:50 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 07:25:34 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJSPHERE_H
# define FT_OBJSPHERE_H

#include "ft_ray.h"
#include "ft_obj_base.h"

typedef struct s_obj_sphere
{
	/* data */

	t_obj_base *objectbase;
}	t_obj_sphere;


bool	ft_objsphere_intersection(t_ray *ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color);

#endif
