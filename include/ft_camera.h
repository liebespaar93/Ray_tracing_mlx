/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:38:51 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 16:29:09 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CAMERA_H
# define FT_CAMERA_H

# include <stdbool.h>
# include "ft_vector.h"
# include "ft_ray.h"

typedef struct s_camera
{
	/* data */
	t_vec3	position;
	t_vec3	look_at;
	t_vec3	up;

	double	length;
	double	horzsize;
	double	aspect_ratio;


	t_vec3	alignment;
	t_vec3	screen_u;
	t_vec3	screen_v;
	t_vec3	screen_center;

		
}	t_camera;



t_camera	*ft_camera_init();
void		ft_camera_update_geometry(t_camera *camera);
bool		ft_camera_generate_ray(t_camera *camera, double screen_x, double screen_y, t_ray *camera_ray);

#endif
