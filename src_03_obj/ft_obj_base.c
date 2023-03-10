/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:59:24 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/17 20:18:04 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <errno.h>
#include <stdlib.h>

#include "ft_obj_base.h"
#include "ft_tool.h"

t_obj_base *ft_obj_base_set(char *type, void *ptr)
{
	t_obj_base *obj_base;

	if (!ft_zeromalloc((void **)&obj_base, sizeof(t_obj_base)))
		ft_exit_print_error(ENOMEM, "ft_obj_base_set()");
	
	obj_base->type = type;
	obj_base->obj = ptr;
	obj_base->next = NULL;
	obj_base->material = NULL;
	return (obj_base);
}

t_obj_base *ft_obj_base_pushback(t_obj_base **obj_base_ptr, char *type,void *ptr)
{
	t_obj_base *new;
	t_obj_base *last;

	new = ft_obj_base_set(type, ptr);
	if(!obj_base_ptr || !*obj_base_ptr)
		return (ft_ptrcpy((void **)obj_base_ptr, new));
	last = *obj_base_ptr;
	while (last->next)
		last = last->next;
	last->next = new;
	return (*obj_base_ptr);
}

t_obj_base *ft_obj_base_at(t_obj_base *obj_base, size_t index)
{
	while (obj_base && index)
	{
		obj_base = obj_base->next;
		index--;
	}
	if (index)
		return (NULL);
	return (obj_base);
}

t_vec3	*ft_obj_base_get_color(t_obj_base *obj_base)
{
	t_vec3	*base_color;
	
	base_color = NULL;
	if (!ft_strcmp(obj_base->type, "obj_sphere"))
		base_color = &((t_obj_sphere *)obj_base->obj)->base_color;
	else if (!ft_strcmp(obj_base->type, "obj_plane"))
		base_color = &((t_obj_plane *)obj_base->obj)->base_color;
	else if (!ft_strcmp(obj_base->type, "obj_cylinder"))
		base_color = &((t_obj_cylinder *)obj_base->obj)->base_color;
	else if (!ft_strcmp(obj_base->type, "obj_cone"))
		base_color = &((t_obj_cone *)obj_base->obj)->base_color;
	return (base_color);

}

bool	ft_obj_base_set_transform(t_obj_base *obj_base, t_gt gt)
{
	if (!ft_strcmp(obj_base->type, "obj_sphere"))
		((t_obj_sphere *)obj_base->obj)->gt = gt;
	else if (!ft_strcmp(obj_base->type, "obj_plane"))
		((t_obj_plane *)obj_base->obj)->gt = gt;
	else if (!ft_strcmp(obj_base->type, "obj_cylinder"))
		((t_obj_cylinder *)obj_base->obj)->gt = gt;
	else if (!ft_strcmp(obj_base->type, "obj_cone"))
		((t_obj_cone *)obj_base->obj)->gt = gt;
	else
		return (false);
	return (true);
}

bool	ft_obj_base_set_color(t_obj_base *obj_base, t_vec3 color)
{
	if (!ft_strcmp(obj_base->type, "obj_sphere"))
		((t_obj_sphere *)obj_base->obj)->base_color = color;
	else if (!ft_strcmp(obj_base->type, "obj_plane"))
		((t_obj_plane *)obj_base->obj)->base_color = color;
	else if (!ft_strcmp(obj_base->type, "obj_cylinder"))
		((t_obj_cylinder *)obj_base->obj)->base_color = color;
	else if (!ft_strcmp(obj_base->type, "obj_cone"))
		((t_obj_cone *)obj_base->obj)->base_color = color;
	else
		return (false);
	return (true);

}

bool	ft_obj_base_intersection(t_obj_base *obj_base, t_ray *cast_ray, t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *local_color)
{
	bool	result;

	result = false;
	if (!ft_strcmp(obj_base->type, "obj_sphere"))
		result = ft_obj_sphere_intersection((t_obj_sphere *)obj_base->obj, cast_ray, int_point, local_normal, local_color);
	else if (!ft_strcmp(obj_base->type, "obj_plane"))
		result = ft_obj_plane_intersection((t_obj_plane *)obj_base->obj, cast_ray, int_point, local_normal, local_color);
	else if (!ft_strcmp(obj_base->type, "obj_cylinder"))
		result = ft_obj_cylinder_intersection((t_obj_cylinder *)obj_base->obj, cast_ray, int_point, local_normal, local_color);
	else if (!ft_strcmp(obj_base->type, "obj_cone"))
		result = ft_obj_cone_intersection((t_obj_cone *)obj_base->obj, cast_ray, int_point, local_normal, local_color);
	return (result);
}

bool	ft_obj_close_enough(const double f1, const double f2)
{
	return (fabs(f1- f2) < 1e-21f);
}
