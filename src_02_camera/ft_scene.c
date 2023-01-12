/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:52:16 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/12 14:14:11 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_scene.h"
#include "ft_image.h"


bool	ft_scene_render(t_image	*image)
{
	int x;
	int y;
	t_color color;

	x = 0;
	y = 0;
	color.integer = 0;
	while (y < image->m_y_size)
	{
		x = 0;
		while (x < image->m_x_size)
		{
			color.bit.r = ((double)x / image->m_x_size) * 255.0;
			color.bit.g = ((double)y / image->m_y_size) * 255.0;
			ft_image_set_pixel(image, x, y, (const double [3]){color.bit.r, color.bit.g, 0.0});
			x++;
		}
		y++;
	}
	return (1);
}
