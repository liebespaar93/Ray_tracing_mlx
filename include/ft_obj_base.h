/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_base.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:59:26 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/14 23:36:52 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJECTBASE_H
# define FT_OBJECTBASE_H

# include <stdbool.h>
# include <sys/_types/_size_t.h>


# include "ft_vector.h"
# include "ft_obj_sphere.h"

typedef	struct s_obj_base	t_obj_base;
typedef	struct s_obj_base
{
	/* data */
	char		*type;
	void		*obj;
	t_obj_base	*next;
	
}	t_obj_base;

t_obj_base *ft_obj_base_set(char *type, void *ptr);
t_obj_base *ft_obj_base_pushback(t_obj_base **obj_base_ptr, char *type, void *ptr);
t_obj_base *ft_obj_base_at(t_obj_base *obj_base, size_t index);

bool	ft_obj_base_set_transform(t_obj_base *obj_base, t_gt gt);
bool	ft_obj_base_set_color(t_obj_base *obj_base, t_vec3 color);
bool	ft_obj_base_intersection(t_obj_base *obj_base, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color);

#endif