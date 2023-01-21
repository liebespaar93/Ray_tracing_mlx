/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_point.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:18:44 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/14 11:36:04 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIGHT_POINT_H
# define FT_LIGHT_POINT_H

# include <stdbool.h>

# include "ft_vector.h"
# include "ft_obj_base.h"

typedef struct s_light_point
{
	/* data */
	t_vec3	color;
	t_vec3	location;
	double	intensity;
}	t_light_point;

t_light_point	*ft_light_point_set();
bool	ft_light_point_illumination(t_light_point *light_point, t_vec3 *int_point, t_vec3 *local_normal \
	, t_obj_base *obj_base_list \
	, t_obj_base *current_obj\
	, t_vec3 *color, double *intensity);

#endif
