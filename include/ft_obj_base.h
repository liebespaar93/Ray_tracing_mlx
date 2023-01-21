/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_base.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:59:26 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/17 20:18:04 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_OBJ_BASE_H
# define FT_OBJ_BASE_H

# include <stdbool.h>
# include <sys/_types/_size_t.h>

typedef	struct s_obj_base	t_obj_base;

# include "ft_vector.h"
# include "ft_obj_sphere.h"
# include "ft_obj_plane.h"
# include "ft_obj_cylinder.h"
# include "ft_obj_cone.h"

# include "ft_material_base.h"

typedef	struct s_obj_base
{
	/* data */
	char			*type;
	void			*obj;

	t_material_base	*material;

	t_obj_base		*next;
}	t_obj_base;


t_obj_base *ft_obj_base_set(char *type, void *ptr);
t_obj_base *ft_obj_base_pushback(t_obj_base **obj_base_ptr, char *type, void *ptr);
t_obj_base *ft_obj_base_at(t_obj_base *obj_base, size_t index);

t_vec3	*ft_obj_base_get_color(t_obj_base *obj_base);

bool	ft_obj_base_set_transform(t_obj_base *obj_base, t_gt gt);
bool	ft_obj_base_set_color(t_obj_base *obj_base, t_vec3 color);

bool	ft_obj_base_intersection(t_obj_base *obj_base, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color);

bool	ft_obj_close_enough(const double f1, const double f2);

#endif