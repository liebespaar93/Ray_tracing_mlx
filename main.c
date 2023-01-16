/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:28:42 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/16 15:44:29 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_app.h"
#include "mlx.h"
#include "ft_vector.h"
#include "ft_tool.h"
#include "ft_material_base.h"

#include <stdio.h>

void	ft_test_camera(t_app *app)
{
	app->scene->camera = ft_camera_init();
	app->scene->camera->position = ft_vector_3(0.0, -10.0, -2.0);
	app->scene->camera->look_at = ft_vector_3(0.0, 0.0, 0.0);
	app->scene->camera->up = ft_vector_3(0.0, 0.0, 1.0);
	app->scene->camera->horzsize = 0.25;
	app->scene->camera->aspect_ratio = 16.0 / 9.0;
	ft_camera_update_geometry(app->scene->camera);
}

void	ft_test_light(t_app *app)
{
	app->scene->light_list = ft_light_base_pushback(&app->scene->light_list, "light_point", ft_light_point_set());
	app->scene->light_list = ft_light_base_pushback(&app->scene->light_list, "light_point", ft_light_point_set());
	app->scene->light_list = ft_light_base_pushback(&app->scene->light_list, "light_point", ft_light_point_set());
	
	ft_light_location_set(ft_light_base_at(app->scene->light_list, 0), ft_vector_3(5.0, -10.0, -5.0));
	ft_light_location_set(ft_light_base_at(app->scene->light_list, 1), ft_vector_3(-5.0, -10.0, -5.0));
	ft_light_location_set(ft_light_base_at(app->scene->light_list, 2), ft_vector_3(0.0, -10.0, -5.0));
	
	ft_light_color_set(ft_light_base_at(app->scene->light_list, 0), ft_vector_3(0.0, 0.0, 1.0));
	ft_light_color_set(ft_light_base_at(app->scene->light_list, 1), ft_vector_3(1.0, 0.0, 0.0));
	ft_light_color_set(ft_light_base_at(app->scene->light_list, 2), ft_vector_3(0.0, 1.0, 0.0));

}


void	ft_test_obj_sphere(t_app *app)
{
	t_gt		test_gt[3];

	test_gt[0] = ft_gt_default();
	test_gt[1] = ft_gt_default();
	test_gt[2] = ft_gt_default();

	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_sphere", ft_obj_sphere_set());
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_sphere", ft_obj_sphere_set());
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_sphere", ft_obj_sphere_set());
	
	ft_gt_transform(&test_gt[0], ft_vector_3(-1.5, 0.0, 0.0), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(0.5, 0.5, 0.5));
	ft_gt_transform(&test_gt[1], ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(0.5, 0.5, 0.5));
	ft_gt_transform(&test_gt[2], ft_vector_3(1.5, 0.0, 0.0), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(0.5, 0.5, 0.5));

	ft_obj_base_set_transform(ft_obj_base_at(app->scene->obj_list, 0), test_gt[0]);
	ft_obj_base_set_transform(ft_obj_base_at(app->scene->obj_list, 1), test_gt[1]);
	ft_obj_base_set_transform(ft_obj_base_at(app->scene->obj_list, 2), test_gt[2]);

	ft_obj_base_set_color(ft_obj_base_at(app->scene->obj_list, 0), ft_vector_3(0.25, 0.5, 0.8));
	ft_obj_base_set_color(ft_obj_base_at(app->scene->obj_list, 1), ft_vector_3(1.0, 0.5, 0.0));
	ft_obj_base_set_color(ft_obj_base_at(app->scene->obj_list, 2), ft_vector_3(1.0, 0.8, 0.0));
}

void	ft_test_obj_plane(t_app *app)
{
	t_gt		test_gt;

	test_gt = ft_gt_default();
	ft_gt_transform(&test_gt, ft_vector_3(0.0, 0.0, 0.75), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(4.0, 4.0, 4.0));
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_plane", ft_obj_plane_set());
	ft_obj_base_set_transform(ft_obj_base_at(app->scene->obj_list, 3), test_gt);
	ft_obj_base_set_color(ft_obj_base_at(app->scene->obj_list, 3), ft_vector_3(0.5, 0.5, 0.5));
}

void	ft_test_material(t_app *app)
{
	t_material_base *material[3];
	t_material_base *floor_matrial;

	material[0] = ft_materia_base_set("simple", ft_material_simple_default());
	material[1] = ft_materia_base_set("simple", ft_material_simple_default());
	material[2] = ft_materia_base_set("simple", ft_material_simple_default());
	
	ft_materia_base_set_color(material[0], ft_vector_3(0.25, 0.5, 0.8));
	ft_materia_base_set_reflectivity(material[0], 0.1);
	ft_materia_base_set_shininess(material[0], 10.0);

	ft_materia_base_set_color(material[1], ft_vector_3(0.5, 0.5, 0.5));
	ft_materia_base_set_reflectivity(material[1], 0.75);
	ft_materia_base_set_shininess(material[1], 10.0);
	
	ft_materia_base_set_color(material[2], ft_vector_3(1.0, 0.8, 0.0));
	ft_materia_base_set_reflectivity(material[2], 0.25);
	ft_materia_base_set_shininess(material[2], 10.0);
	
	floor_matrial = ft_materia_base_set("simple", ft_material_simple_default());

	ft_materia_base_set_color(floor_matrial, ft_vector_3(1.0, 1.0, 1.0));
	ft_materia_base_set_reflectivity(floor_matrial, 0.5);
	ft_materia_base_set_shininess(floor_matrial, 0.0);
	
	ft_obj_base_at(app->scene->obj_list, 0)->material = material[2];
	ft_obj_base_at(app->scene->obj_list, 1)->material = material[0];
	ft_obj_base_at(app->scene->obj_list, 2)->material = material[1];
	ft_obj_base_at(app->scene->obj_list, 3)->material = floor_matrial;
}

int main(int argc, char const *argv[])
{
	t_app	*app;
	
	/* code */
	(void)argc;
	(void)argv;
	app = ft_app_init();
	ft_test_camera(app);
	ft_test_light(app);
	ft_test_obj_sphere(app);
	ft_test_obj_plane(app);
	ft_test_material(app);
	ft_app_execute(app);

	system("leaks a.out");
	(void)app;
	return 0;
}
