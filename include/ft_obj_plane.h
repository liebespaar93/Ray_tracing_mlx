/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_plane.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:21:50 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/15 17:34:31 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJ_PLANE_H
# define FT_OBJ_PLANE_H

# include "ft_vector.h"
# include "ft_geometric_transform.h"

typedef struct s_obj_plane
{
	/* data */
	t_vec3	base_color;
	t_gt	gt;

}	t_obj_plane;


t_obj_plane		*ft_obj_plane_set();
bool			ft_obj_plane_intersection(t_obj_plane *obj_plane, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color);



#endif
