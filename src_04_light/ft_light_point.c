/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:24:33 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/14 12:01:08 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <errno.h>
#include <math.h>

#include "ft_light_point.h"
#include "ft_tool.h"

t_light_point	*ft_light_point_set()
{
	t_light_point	*light_point;

	if (!ft_zeromalloc((void **)&light_point, sizeof(t_light_point)))
		ft_exit_print_error(ENOMEM, "ft_light_point_set()");
	
	light_point->color = ft_vector_3(1.0, 1.0, 1.0);
	light_point->intensity = 1.0;
	light_point->location = ft_vector_3(0.0, 0.0, 0.0);
	
	return (light_point);
}

bool	ft_light_point_illumination(t_light_point *light_point, t_vec3 *int_point, t_vec3 *local_normal \
	, t_obj_base *obj_base_list \
	, t_obj_base *current_obj\
	, t_vec3 *color, double *intensity)
{
	(void)obj_base_list;
	(void)current_obj;
	
	t_vec3 light_dir = ft_vec3_normalize(ft_vec3_sub(light_point->location, *int_point));
	t_vec3 start_point = *int_point;
	(void)start_point;
	double angle = acos(ft_vec3_dot(*local_normal, light_dir));

	if (angle > 1.5700)
	{
		*color = light_point->color;
		*intensity = 0.0;
		return (false);
	}
	else
	{
		*color = light_point->color;
		*intensity = light_point->intensity * (1.0 - (angle / 1.5700));
		return (true);
	}
}