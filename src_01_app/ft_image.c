/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:41:30 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/12 13:55:38 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "mlx.h"

#include "ft_image.h"
#include "ft_tool.h"

t_image	*ft_image_set()
{
	t_image	*image;

	if (!ft_zeromalloc((void **)&image, sizeof(t_image)))
		ft_exit_print_error(ENOMEM, "ft_image_set()");
	image->m_x_size = 0;
	image->m_y_size = 0;
	image->m_rchannel = NULL;
	image->m_gchannel = NULL;
	image->m_bchannel = NULL;
	image->temp_pixel = NULL;
	return (image);	
}

void	ft_image_destroy(t_image *image)
{
	if (!image)
		return ;
	if (image->m_rchannel)
		free(image->m_rchannel);
	if (image->m_gchannel)
		free(image->m_gchannel);
	if (image->m_bchannel)
		free(image->m_bchannel);
	if (image->temp_pixel)
		free(image->temp_pixel);
}

t_image	*ft_image_init(const int x_size, const int y_size)
{
	t_image	*image;

	image = ft_image_set();
	image->m_x_size = x_size;
	image->m_y_size = y_size;

	if (!ft_zeromalloc((void **)&image->m_rchannel, sizeof(double) * (x_size * y_size )) || \
		!ft_zeromalloc((void **)&image->m_gchannel, sizeof(double) * (x_size * y_size )) || \
		!ft_zeromalloc((void **)&image->m_bchannel, sizeof(double) * (x_size * y_size )) || \
		!ft_zeromalloc((void **)&image->temp_pixel, sizeof(t_color) * (x_size * y_size )))
		ft_image_destroy(image);
	return (image);
}

int	ft_image_set_pixel(t_image *image, const int x, const int y, const double color[3])
{
	int	point;

	if (x < 0 || image->m_x_size <= x || y < 0 || image->m_y_size <= y)
		return (0);
	point = y * image->m_x_size + x;
	image->m_rchannel[point] = color[0];
	image->m_gchannel[point] = color[1];
	image->m_bchannel[point] = color[2];
	return (1);
}

void	ft_image_display(t_image *image, bool endian)
{
	int	x;
	int	y;

	y = -1;
	while (y++ < image->m_y_size)
	{
		x = -1;
		while (x++ < image->m_x_size)
			ft_image_convert_color(image, y * image->m_x_size + x, endian);
	}
}

void	ft_image_convert_color(t_image *image, int point, bool endian)
{
	if (endian)
	{
		image->temp_pixel[point].bit.a = image->m_bchannel[point];
		image->temp_pixel[point].bit.r = image->m_gchannel[point];
		image->temp_pixel[point].bit.g = image->m_rchannel[point];
		image->temp_pixel[point].bit.b = 0;
	}
	else
	{
		image->temp_pixel[point].bit.a = 0;
		image->temp_pixel[point].bit.r = image->m_rchannel[point];
		image->temp_pixel[point].bit.g = image->m_gchannel[point];
		image->temp_pixel[point].bit.b = image->m_bchannel[point];
	}
}