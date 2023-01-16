/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_material_base.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:52:58 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/16 13:08:39 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATERIAL_BASE_H
# define FT_MATERIAL_BASE_H

typedef	struct s_material_base	t_material_base;

# include "ft_vector.h"
# include "ft_obj_base.h"
# include "ft_light_base.h"
# include "ft_material_simple.h"

typedef	struct s_material_base
{
	/* data */
	char			*type;
	void			*material;

	int		max_reflection_rays;
	int		reflection_ray_count;
}	t_material_base;

t_material_base *ft_materia_base_set(char *type, void *material);


bool ft_materia_base_set_color(t_material_base *materia_base, t_vec3 base_color);
bool ft_materia_base_set_reflectivity(t_material_base *materia_base, double reflectivity);
bool ft_materia_base_set_shininess(t_material_base *materia_base, double shininess);

t_vec3	ft_material_base_compute_color(t_material_base *material_base, t_obj_base *obj_list, t_light_base *light_list, t_obj_base *current_obj,
	t_vec3 *int_point, t_vec3 *local_normal, t_ray *camera_ray);

t_vec3	ft_material_base_diffuse_color(t_obj_base *obj_list, t_light_base *light_list, t_obj_base *current_obj,
	t_vec3 *int_point, t_vec3 *local_normal, t_vec3 *base_color);

t_vec3	ft_material_base_compute_reflection_color(t_material_base *material_base, t_obj_base *obj_list, t_light_base *light_list, t_obj_base *current_obj,
	t_vec3 *int_point, t_vec3 *local_normal, t_ray *incident_ray);

bool	ft_material_base_cast_ray(t_ray *cast_ray, t_obj_base *obj_list, t_obj_base *this_obj, \
	t_obj_base **closest_obj, t_vec3 *closest_int_point, t_vec3 *closest_local_normal, t_vec3 *closest_local_color);

#endif
