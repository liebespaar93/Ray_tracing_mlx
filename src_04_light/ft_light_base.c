/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:08:01 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/15 13:58:01 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "ft_light_base.h"

#include "ft_tool.h"

t_light_base	*ft_light_base_set(char *type, void *light)
{
	t_light_base	*light_base;

	if (!ft_zeromalloc((void **)&light_base, sizeof(t_light_base)))
		ft_exit_print_error(ENOMEM, "ft_light_base_set()");
	
	light_base->type = type;
	light_base->light = light;
	light_base->next = NULL;

	return (light_base);
}


t_light_base	*ft_light_base_pushback(t_light_base **light_base_ptr, char *type, void *light)
{
	t_light_base	*new;
	t_light_base	*last;
	
	new = ft_light_base_set(type, light);
	if (!light_base_ptr || !*light_base_ptr)
		return (ft_ptrcpy((void **)light_base_ptr, new));
	last = *light_base_ptr;
	while (last->next)
		last = last->next;
	last->next = new;
	return (*light_base_ptr);
}

t_light_base	*ft_light_base_at(t_light_base *light_base, size_t index)
{
	while (light_base && index)
	{
		light_base = light_base->next;
		index--;
	}
	if (index)
		return (NULL);
	return (light_base);
}


bool	ft_light_location_set(t_light_base *light_base, t_vec3 location)
{
	if (!ft_strcmp(light_base->type, "light_point"))
		((t_light_point *)light_base->light)->location = location;
	else
		return (false);
	return (true);
}


bool	ft_light_color_set(t_light_base *light_base, t_vec3 location)
{
	if (!ft_strcmp(light_base->type, "light_point"))
		((t_light_point *)light_base->light)->color = location;
	else
		return (false);
	return (true);
}


bool	ft_light_illumination(t_light_base *light_base, t_vec3 *int_point, t_vec3 *local_normal \
	, t_obj_base *obj_base_list \
	, t_obj_base *current_obj\
	, t_vec3 *color, double *intensity)
{
	bool	result;

	result = false;
	if (!ft_strcmp(light_base->type, "light_point"))
		result = ft_light_point_illumination((t_light_point *)light_base->light, int_point, local_normal, obj_base_list, current_obj, color, intensity);
	return (result);
}