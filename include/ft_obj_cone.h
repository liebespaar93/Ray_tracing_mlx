/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_cone.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:08:52 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/17 19:09:18 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJ_CONE_H
# define FT_OBJ_CONE_H

#include <stdbool.h>
#include "ft_ray.h"

# include "ft_geometric_transform.h"

typedef	struct s_obj_cone
{
	/* data */
	t_vec3	base_color;
	t_gt	gt;
	
}	t_obj_cone;


t_obj_cone	*ft_obj_cone_set();

bool	ft_obj_cone_intersection(t_obj_cone *obj_cone, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color);


#endif
