/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_base.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:04:03 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/15 13:58:12 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_LIGHT_BASE_H
# define FT_LIGHT_BASE_H

# include <stdbool.h>

#include "ft_vector.h"
#include "ft_light_point.h"

typedef	struct s_light_base	t_light_base;
typedef	struct s_light_base
{
	/* data */

	char			*type;
	void			*light;
	t_light_base	*next;
}	t_light_base;


t_light_base	*ft_light_base_set(char *type, void *light);

t_light_base	*ft_light_base_pushback(t_light_base **light_base_ptr, char *type, void *light);
t_light_base	*ft_light_base_at(t_light_base *light_base, size_t index);

bool			ft_light_location_set(t_light_base *light_base, t_vec3 location);
bool			ft_light_color_set(t_light_base *light_base, t_vec3 location);

bool	ft_light_illumination(t_light_base *light_base, t_vec3 *int_point, t_vec3 *local_normal \
	, t_obj_base *obj_base_list \
	, t_obj_base *current_obj\
	, t_vec3 *color, double *intensity);

#endif
