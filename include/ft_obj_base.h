/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_base.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:59:26 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 07:18:58 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJECTBASE_H
# define FT_OBJECTBASE_H

# include <stdbool.h>

# include "ft_vector.h"

typedef	struct s_obj_base
{
	/* data */
	t_vec3	basecolor;
	
}	t_obj_base;

#endif