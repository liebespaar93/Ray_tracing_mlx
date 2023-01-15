/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:28:26 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/15 13:33:00 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IMAGE_H
# define FT_IMAGE_H

# include <stdbool.h>

typedef union s_color
{
	unsigned int	integer;
	struct bit
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	} bit;
}	t_color;

typedef struct s_image
{
	/* data */
	int		x_size;
	int		y_size;
	
	double	*rchannel;
	double	*gchannel;
	double	*bchannel;

	double	max_red;
	double	max_green;
	double	max_blue;
	double	max_overall;

	t_color		*temp_pixel;
}	t_image;


t_image	*ft_image_set();

void	ft_image_destroy(t_image *image);
t_image	*ft_image_init(const int x_size, const int y_size);
int		ft_image_set_pixel(t_image *image, const int x, const int y, const double color[3]);
void	ft_image_display(t_image *image, bool endian);
void	ft_image_convert_color(t_image *image, int point, bool endian);
void	ft_image_compute_max_values(t_image *image);

#endif
