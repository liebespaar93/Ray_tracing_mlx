/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 05:39:34 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/12 15:25:42 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_APP_H
# define FT_APP_H

# ifndef WIN_WIDTH
# define WIN_WIDTH   1200
# endif

# ifndef WIN_HEIGHT
# define WIN_HEIGHT  700
# endif

# define SCREEN_X		0
# define SCREEN_Y		0
# define SCREEN_WIDTH	WIN_WIDTH
# define SCREEN_HEIGHT	WIN_HEIGHT

# include <stdbool.h>

# include "ft_image.h"
# include "ft_scene.h"
# include "ft_camera.h"

typedef struct s_app t_app;

typedef struct s_mlx
{
	/* data */
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;

}	t_mlx;

typedef	struct s_renderer
{
	/* data */
	char		*buffer;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

}	t_renderer;

typedef struct s_app
{
	/* data */
	bool		isrunning;
	t_mlx		*mlx;
	t_renderer	*renderer;
	t_image		*image;
	t_scene		*scene;
	t_camera	*camera;
}	t_app;


t_app	*ft_app_set();
t_app	*ft_app_init();
void	ft_app_render(t_app *app);

int		ft_app_event(t_app *app);
void	ft_app_exit(t_app *app);

void	ft_app_execute(t_app *app);


#endif


