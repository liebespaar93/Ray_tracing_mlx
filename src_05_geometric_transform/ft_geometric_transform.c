/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_geometric_transform.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:36:39 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/15 11:39:48 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "ft_geometric_transform.h"
#include "ft_tool.h"

t_gt	ft_gt_default()
{
	t_gt	gt;

	gt.forward_to_form = true;
	gt.back_to_form = false;
	gt.forward_tf_mtx = ft_mtx4_identity();
	gt.back_tf_mtx = ft_mtx4_identity();

	return(gt);
}

void	ft_gt_transform(t_gt *gt, t_vec3 translation, t_vec3 rotation, t_vec3 scale)
{
	t_mtx4	translation_mtx;
	t_mtx4	rotation_mtx_x;
	t_mtx4	rotation_mtx_y;
	t_mtx4	rotation_mtx_z;
	t_mtx4	scale_mtx;

	translation_mtx = ft_mtx4_translation(translation.x, translation.y, translation.z);

	rotation_mtx_x = ft_mtx4_rot_x(rotation.x);
	rotation_mtx_y = ft_mtx4_rot_y(rotation.y);
	rotation_mtx_z = ft_mtx4_rot_z(rotation.z);
	scale_mtx = ft_mtx4_scale(scale.x, scale.y, scale.z);

	gt->forward_tf_mtx = ft_mtx4_mult_mtx4(gt->forward_tf_mtx, translation_mtx);
	gt->forward_tf_mtx = ft_mtx4_mult_mtx4(gt->forward_tf_mtx, scale_mtx);
	gt->forward_tf_mtx = ft_mtx4_mult_mtx4(gt->forward_tf_mtx, rotation_mtx_x);
	gt->forward_tf_mtx = ft_mtx4_mult_mtx4(gt->forward_tf_mtx, rotation_mtx_y);
	gt->forward_tf_mtx = ft_mtx4_mult_mtx4(gt->forward_tf_mtx, rotation_mtx_z);
	
	gt->back_tf_mtx = ft_mtx4_inverse(gt->forward_tf_mtx);
}

t_ray	ft_gt_apply(t_gt *gt, t_ray *input_ray, bool *dir_flag)
{
	t_ray	output_ray;

	if (*dir_flag)
	{
		output_ray.point1 = ft_gt_apply_vec3(gt, &input_ray->point1, &gt->forward_to_form);
		output_ray.point2 = ft_gt_apply_vec3(gt, &input_ray->point2, &gt->forward_to_form);
		output_ray.lab = ft_vec3_sub(output_ray.point2, output_ray.point1);
	}
	else
	{
		output_ray.point1 = ft_gt_apply_vec3(gt, &input_ray->point1, &gt->back_to_form);
		output_ray.point2 = ft_gt_apply_vec3(gt, &input_ray->point2, &gt->back_to_form);
		output_ray.lab = ft_vec3_sub(output_ray.point2, output_ray.point1);
	}

	return (output_ray);
}

t_vec3	ft_gt_apply_vec3(t_gt *gt, t_vec3 *input_v3, bool *dir_flag)
{
	t_vec3	output_v3;

	if (*dir_flag)
		output_v3 = ft_mtx4_mult_vec3(gt->forward_tf_mtx, *input_v3);
	else
		output_v3 = ft_mtx4_mult_vec3(gt->back_tf_mtx, *input_v3);
	return (output_v3);
}

t_gt	ft_gt_mult(t_gt *lhs, t_gt *rhs)
{
	t_gt	new;

	new = ft_gt_default();
	new.forward_tf_mtx = ft_mtx4_mult_mtx4(lhs->forward_tf_mtx, rhs->forward_tf_mtx);
	new.back_tf_mtx = ft_mtx4_inverse(new.forward_tf_mtx);

	return (new);
}

t_gt	ft_gt_cpy(t_gt *gt)
{
	t_gt	new;

	new = ft_gt_default();
	new.forward_tf_mtx = gt->forward_tf_mtx;
	new.back_tf_mtx = gt->back_tf_mtx;
	return (new);
}

void	ft_gt_print(t_gt *gt, bool *dir_flag)
{
	if (*dir_flag)
		ft_print_mtx4(&gt->forward_tf_mtx);
	else
		ft_print_mtx4(&gt->back_tf_mtx);
}

#include <stdio.h>
void	ft_print_mtx4(t_mtx4 *m4)
{
	printf(" | %+5.3f %+5.3f %+5.3f %+5.3f | \n", m4->m11, m4->m12, m4->m13, m4->m14);
	printf(" | %+5.3f %+5.3f %+5.3f %+5.3f | \n", m4->m21, m4->m22, m4->m23, m4->m24);
	printf(" | %+5.3f %+5.3f %+5.3f %+5.3f | \n", m4->m31, m4->m32, m4->m33, m4->m34);
	printf(" | %+5.3f %+5.3f %+5.3f %+5.3f | \n", m4->m41, m4->m42, m4->m43, m4->m44);
	printf(" == \n");
}

void	ft_print_vec3(t_vec3 *v3)
{
	printf(" | %+5.3f %+5.3f %+5.3f | \n", v3->x, v3->y, v3->z);
	printf(" == \n");
}