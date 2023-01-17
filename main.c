/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:28:42 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/17 22:24:55 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "ft_app.h"
#include "mlx.h"
#include "ft_vector.h"
#include "ft_tool.h"
#include "ft_obj_base.h"
#include "ft_material_base.h"

#include <stdio.h>

void	ft_test_camera(t_app *app)
{
	app->scene->camera = ft_camera_init();
	app->scene->camera->position = ft_vector_3(3.0, -5.0, -2.0);
	app->scene->camera->look_at = ft_vector_3(0.0, 0.0, 0.0);
	app->scene->camera->up = ft_vector_3(0.0, 0.0, 1.0);
	app->scene->camera->horzsize = 0.75;
	app->scene->camera->aspect_ratio = 16.0 / 9.0;
	ft_camera_update_geometry(app->scene->camera);
}

void	ft_test_light(t_app *app)
{
	app->scene->light_list = ft_light_base_pushback(&app->scene->light_list, "light_point", ft_light_point_set());
	app->scene->light_list = ft_light_base_pushback(&app->scene->light_list, "light_point", ft_light_point_set());
	app->scene->light_list = ft_light_base_pushback(&app->scene->light_list, "light_point", ft_light_point_set());
	
	ft_light_location_set(ft_light_base_at(app->scene->light_list, 0), ft_vector_3(3.0, -10.0, -5.0));
	ft_light_location_set(ft_light_base_at(app->scene->light_list, 1), ft_vector_3(0.0, -10.0, -5.0));
	
	ft_light_color_set(ft_light_base_at(app->scene->light_list, 0), ft_vector_3(1.0, 1.0, 1.0));
	ft_light_color_set(ft_light_base_at(app->scene->light_list, 1), ft_vector_3(1.0, 1.0, 1.0));

}


void	ft_test_obj_sphere(t_app *app)
{
	t_obj_sphere		*left_sphere;
	t_obj_sphere		*right_sphere;
	t_obj_sphere		*top_sphere;


	left_sphere = ft_obj_sphere_set();
	left_sphere->base_color = ft_vector_3(0.0, 0.0, 0.0);
	left_sphere->gt = ft_gt_set(ft_vector_3(1.5, -2.0, 0.5), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(0.5, 0.5, 0.5));

	right_sphere = ft_obj_sphere_set();
	right_sphere->base_color = ft_vector_3(0.0, 0.0, 0.0);
	right_sphere->gt = ft_gt_set(ft_vector_3(1.5, 0.0, 0.0), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(1.0, 1.0, 1.0));

	top_sphere = ft_obj_sphere_set();
	top_sphere->base_color = ft_vector_3(0.0, 0.0, 0.0);
	top_sphere->gt = ft_gt_set(ft_vector_3(0.0, 0.0, -1.0), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(0.5, 0.5, 0.5));

	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_sphere", left_sphere);
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_sphere", right_sphere);
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_sphere", top_sphere);
}

void	ft_test_obj_plane(t_app *app)
{
	t_obj_plane		*floot_plane;
	t_obj_plane	*left_wall_plane;
	t_obj_plane	*back_wall_plane;


	floot_plane = ft_obj_plane_set();
	floot_plane->base_color = ft_vector_3(0.0, 0.0, 0.0);
	floot_plane->gt = ft_gt_set(ft_vector_3(0.0, 0.0, 1.0), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(16.0, 16.0, 1.0));

	left_wall_plane = ft_obj_plane_set();
	left_wall_plane->base_color = ft_vector_3(0.0, 0.0, 0.0);
	left_wall_plane->gt = ft_gt_set(ft_vector_3(-4.0, 0.0, 0.0), ft_vector_3(0.0, -M_PI/2.0, -M_PI/2.0), ft_vector_3(16.0, 16.0, 1.0));

	back_wall_plane = ft_obj_plane_set();
	back_wall_plane->base_color = ft_vector_3(0.0, 0.0, 0.0);
	back_wall_plane->gt = ft_gt_set(ft_vector_3(0.0, 4.0, 0.0), ft_vector_3(-M_PI/2.0, 0.0, 0.0), ft_vector_3(16.0, 16.0, 1.0));

	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_plane", floot_plane);
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_plane", left_wall_plane);
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_plane", back_wall_plane);
}

void	ft_test_obj_cylinder(t_app *app)
{
	t_obj_cylinder	*cylinder1;
	t_obj_cylinder	*cylinder2;


	cylinder1 = ft_obj_cylinder_set();
	cylinder1->base_color = ft_vector_3(0.0, 0.0, 0.0);
	cylinder1->gt = ft_gt_set(ft_vector_3(-1.5, -2.0, 1.0), ft_vector_3(0.0, -M_PI / 2.0, 0.0), ft_vector_3(0.25, 0.25, 1.0));

	cylinder2 = ft_obj_cylinder_set();
	cylinder2->base_color = ft_vector_3(0.0, 0.0, 0.0);
	cylinder2->gt = ft_gt_set(ft_vector_3(-1.0, -2.0, 0.0), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(0.25, 0.25, 1.0));

	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_cylinder", cylinder1);
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_cylinder", cylinder2);
}


void	ft_test_obj_cone(t_app *app)
{
	t_obj_cone	*cone1;
	t_obj_cone	*cone2;


	cone1 = ft_obj_cone_set();
	cone1->base_color = ft_vector_3(0.0, 0.0, 0.0);
	cone1->gt = ft_gt_set(ft_vector_3(0.0, 0.0, -0.5), ft_vector_3(0.0, 0.0, 0.0), ft_vector_3(1.0, 1.0, 2.0));



	cone2 = ft_obj_cone_set();
	cone2->base_color = ft_vector_3(0.0, 0.0, 0.0);
	cone2->gt = ft_gt_set(ft_vector_3(0.0, -1.0, 0.0), ft_vector_3(M_PI / 4.0, 0.0, 0.0), ft_vector_3(0.5, 0.5, 1.0));

	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_cone", cone1);
	app->scene->obj_list = ft_obj_base_pushback(&app->scene->obj_list, "obj_cone", cone2);
}

void	ft_test_material(t_app *app)
{
	t_material_base *silver_material;
	t_material_base *gold_material;
	t_material_base *blue_material;
	t_material_base *yellow_material;
	t_material_base *orange_material;
	t_material_base *floor_material;
	t_material_base *wall_material;
	
	silver_material = ft_materia_base_set("simple", ft_material_simple_default());

	ft_materia_base_set_color(silver_material, ft_vector_3(0.5, 0.5, 0.8));
	ft_materia_base_set_reflectivity(silver_material, 0.5);
	ft_materia_base_set_shininess(silver_material, 20.0);
	
	gold_material = ft_materia_base_set("simple", ft_material_simple_default());

	ft_materia_base_set_color(gold_material, ft_vector_3(0.8, 0.8, 0.3));
	ft_materia_base_set_reflectivity(gold_material, 0.25);
	ft_materia_base_set_shininess(gold_material, 20.0);
	
	blue_material = ft_materia_base_set("simple", ft_material_simple_default());

	ft_materia_base_set_color(blue_material, ft_vector_3(0.2, 0.2, 0.8));
	ft_materia_base_set_reflectivity(blue_material, 0.05);
	ft_materia_base_set_shininess(blue_material, 5.0);
	
	yellow_material = ft_materia_base_set("simple", ft_material_simple_default());

	ft_materia_base_set_color(yellow_material, ft_vector_3(0.8, 0.8, 0.2));
	ft_materia_base_set_reflectivity(yellow_material, 0.05);
	ft_materia_base_set_shininess(yellow_material, 5.0);

	orange_material = ft_materia_base_set("simple", ft_material_simple_default());

	ft_materia_base_set_color(orange_material, ft_vector_3(1.0, 0.5, 0.0));
	ft_materia_base_set_reflectivity(orange_material, 0.05);
	ft_materia_base_set_shininess(orange_material, 5.0);

	floor_material = ft_materia_base_set("simple", ft_material_simple_default());

	ft_materia_base_set_color(floor_material, ft_vector_3(1.0, 1.0, 1.0));
	ft_materia_base_set_reflectivity(floor_material, 0.0);
	ft_materia_base_set_shininess(floor_material, 0.0);

	wall_material = ft_materia_base_set("simple", ft_material_simple_default());

	ft_materia_base_set_color(wall_material, ft_vector_3(1.0, 0.125, 0.125));
	ft_materia_base_set_reflectivity(wall_material, 0.75);
	ft_materia_base_set_shininess(wall_material, 0.0);
	
	ft_obj_base_at(app->scene->obj_list, 0)->material = blue_material;
	ft_obj_base_at(app->scene->obj_list, 1)->material = yellow_material;
	ft_obj_base_at(app->scene->obj_list, 2)->material = orange_material;
	ft_obj_base_at(app->scene->obj_list, 3)->material = floor_material;
	ft_obj_base_at(app->scene->obj_list, 4)->material = wall_material;
	ft_obj_base_at(app->scene->obj_list, 5)->material = wall_material;
	ft_obj_base_at(app->scene->obj_list, 6)->material = gold_material;
	ft_obj_base_at(app->scene->obj_list, 7)->material = silver_material;
	ft_obj_base_at(app->scene->obj_list, 8)->material = silver_material;
	ft_obj_base_at(app->scene->obj_list, 9)->material = gold_material;
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
	ft_test_obj_cylinder(app);
	ft_test_obj_cone(app);

	ft_test_material(app);
	ft_app_execute(app);

	system("leaks a.out");
	(void)app;
	return 0;
}
