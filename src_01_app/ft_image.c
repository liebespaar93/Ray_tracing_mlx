/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:41:30 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 16:27:26 by kyoulee          ###   ########.fr       */
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
	image->x_size = 0;
	image->y_size = 0;
	image->rchannel = NULL;
	image->gchannel = NULL;
	image->bchannel = NULL;
	image->temp_pixel = NULL;
	return (image);	
}

void	ft_image_destroy(t_image *image)
{
	if (!image)
		return ;
	if (image->rchannel)
		free(image->rchannel);
	if (image->gchannel)
		free(image->gchannel);
	if (image->bchannel)
		free(image->bchannel);
	if (image->temp_pixel)
		free(image->temp_pixel);
}

t_image	*ft_image_init(const int x_size, const int y_size)
{
	t_image	*image;

	image = ft_image_set();

	image->x_size = x_size;
	image->y_size = y_size;

	if (!ft_zeromalloc((void **)&image->rchannel, sizeof(double) * (x_size * y_size )) || \
		!ft_zeromalloc((void **)&image->gchannel, sizeof(double) * (x_size * y_size )) || \
		!ft_zeromalloc((void **)&image->bchannel, sizeof(double) * (x_size * y_size )) || \
		!ft_zeromalloc((void **)&image->temp_pixel, sizeof(t_color) * (x_size * y_size )))
		ft_image_destroy(image);
	return (image);
}

int	ft_image_set_pixel(t_image *image, const int x, const int y, const double color[3])
{
	int	point;

	point = y * image->x_size + x;
	image->rchannel[point] = color[0];
	image->gchannel[point] = color[1];
	image->bchannel[point] = color[2];
	return (1);
}

void	ft_image_display(t_image *image, bool endian)
{
	int	x;
	int	y;

	y = 0;
	while (y < image->y_size)
	{
		x = 0;
		while (x < image->x_size)
		{
			ft_image_convert_color(image, y * image->x_size + x, endian);
			x++;
		}
		y++;
	}
}

void	ft_image_convert_color(t_image *image, int point, bool endian)
{
	if (endian)
	{
		image->temp_pixel[point].bit.a = (unsigned char)image->bchannel[point];
		image->temp_pixel[point].bit.r = (unsigned char)image->gchannel[point];
		image->temp_pixel[point].bit.g = (unsigned char)image->rchannel[point];
		image->temp_pixel[point].bit.b = 0;
	}
	else
	{
		image->temp_pixel[point].bit.a = 0;
		image->temp_pixel[point].bit.r = (unsigned char)image->rchannel[point];
		image->temp_pixel[point].bit.g = (unsigned char)image->gchannel[point];
		image->temp_pixel[point].bit.b = (unsigned char)image->bchannel[point];
	}
}