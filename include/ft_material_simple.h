/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_material_simple.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:16:49 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/16 13:00:30 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATERIAL_SIMPLE_H
# define FT_MATERIAL_SIMPLE_H

# include "ft_material_base.h"
# include "ft_vector.h"

typedef struct s_material_simple
{
	/* data */
	t_vec3	base_color;
	double	reflectivity;
	double	shininess;

}	t_material_simple;

t_material_simple	*ft_material_simple_default();

t_vec3	ft_material_simple_compute_color(t_material_base *material_base, t_material_simple *material_simple, t_obj_base *obj_list, t_light_base *light_list, t_obj_base *current_obj,
	t_vec3 *int_point, t_vec3 *local_normal, t_ray *camera_ray);

t_vec3	ft_material_simple_compute_specular(t_material_simple *material_simple, t_obj_base *obj_list, t_light_base *light_list,
	t_vec3 *int_point, t_vec3 *local_normal, t_ray *camera_ray);



#endif
