/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:50:06 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/15 21:19:27 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "ft_image.h"
# include "ft_camera.h"
# include "ft_obj_base.h"
# include "ft_light_base.h"

typedef struct s_scene
{
	/* data */
	t_camera	*camera;

	t_obj_base	*obj_list;

	t_light_base	*light_list;
	
}	t_scene;

t_scene	*ft_scene_init();
bool	ft_scene_render(t_scene *scene, t_image *image);

bool	ft_scene_cast_ray(t_scene *scene, t_ray *cast_ray, 
	t_obj_base **close_obj, t_vec3 *close_int_point, t_vec3 *close_local_normal, t_vec3 *close_local_color);
#endif
