/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_sylinder.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:13:07 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/17 20:24:06 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJ_cylinder_H
# define FT_OBJ_cylinder_H

#include <stdbool.h>
#include "ft_ray.h"

# include "ft_geometric_transform.h"

typedef	struct s_obj_cylinder
{
	/* data */
	t_vec3	base_color;
	t_gt	gt;
	
}	t_obj_cylinder;


t_obj_cylinder	*ft_obj_cylinder_set();

bool	ft_obj_cylinder_intersection(t_obj_cylinder *obj_cylinder, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color);

#endif
