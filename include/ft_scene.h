/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:50:06 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 11:55:14 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "ft_image.h"
# include "ft_camera.h"
# include "ft_obj_sphere.h"

typedef struct s_scene
{
	/* data */
	t_camera	*camera;
}	t_scene;

t_scene	*ft_scene_init();
bool	ft_scene_render(t_scene *scene, t_image *image);

#endif
