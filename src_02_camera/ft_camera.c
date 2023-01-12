/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:38:44 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/12 15:30:48 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ft_camera.h"

t_camera	ft_camera_init()
{
	t_camera	camera;

	camera.position = ft_vector_3(0.0, -10.0, 0.0);
	camera.look_at = ft_vector_3(0.0, 0.0, 0.0);
	camera.up = ft_vector_3(0.0, 0.0, 1.0);
	camera.length = 1.0;
	camera.horzsize = 1.0;
	camera.aspect_ratio = 1.0;
	return (camera);
}

void	ft_camera_update_geometry(t_camera *camera)
{
	camera->alignment = ft_vec3_sub(camera->look_at, camera->position);
	camera->alignment = ft_vec3_normalize(camera->alignment);


	camera->screen_u = ft_vec3_cross(camera->alignment, camera->up);
	camera->screen_u = ft_vec3_normalize(camera->screen_u);
	camera->screen_v = ft_vec3_cross(camera->screen_u, camera->alignment);
	camera->screen_v = ft_vec3_normalize(camera->screen_v);
	
	camera->screen_center = ft_vec3_add(camera->position, ft_vec3_mult(camera->alignment, camera->length));

	camera->screen_u = ft_vec3_mult(camera->screen_u, camera->horzsize);
	camera->screen_v = ft_vec3_mult(camera->screen_v, camera->horzsize / camera->aspect_ratio);
}

t_ray	ft_camera_generate_ray(t_camera *camera, double screen_x, double screen_y)
{
	t_ray	ray;
	t_vec3	screen_worldpart1;
	t_vec3	screen_world_coordinate;

	screen_worldpart1 = ft_vec3_add(camera->screen_center, ft_vec3_mult(camera->screen_u , screen_x));
	screen_world_coordinate = ft_vec3_add(screen_worldpart1, ft_vec3_mult(camera->screen_v, screen_y));

	ray = ft_ray_set(camera->position, screen_world_coordinate);
	return (ray);
}