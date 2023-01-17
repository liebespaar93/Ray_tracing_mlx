/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_geometric_transform.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:27:27 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/17 12:47:06 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GEOMETRIC_TRANSFORM_H
# define FT_GEOMETRIC_TRANSFORM_H

# include <stdbool.h>
# include "ft_matrix.h"
# include "ft_ray.h"

typedef struct s_geometric_transform
{
	/* data */
	bool forward_to_form;
	bool back_to_form;

	t_mtx4	forward_tf_mtx;
	t_mtx4	back_tf_mtx;
}	t_gt;

t_gt	ft_gt_default();
t_gt	ft_gt_set(t_vec3 translation, t_vec3 rotation, t_vec3 scale);

void	ft_gt_transform(t_gt *gt, t_vec3 translation, t_vec3 rotation, t_vec3 scale);

t_ray	ft_gt_apply(t_gt *gt, t_ray *input_ray, bool *dir_flag);
t_vec3	ft_gt_apply_vec3(t_gt *gt, t_vec3 *input_v3, bool *dir_flag);

t_gt	ft_gt_mult(t_gt *lhs, t_gt *rhs);
t_gt	ft_gt_cpy(t_gt *gt);

void	ft_gt_print(t_gt *gt, bool *dir_flag);
void	ft_print_mtx4(t_mtx4 *m4);
void	ft_print_vec3(t_vec3 *v3);

#endif
