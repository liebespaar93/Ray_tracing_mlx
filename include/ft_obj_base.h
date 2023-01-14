/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_base.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:59:26 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/14 09:17:32 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJECTBASE_H
# define FT_OBJECTBASE_H

# include <stdbool.h>

# include "ft_vector.h"
# include "ft_obj_sphere.h"

typedef	struct s_obj_base	t_obj_base;
typedef	struct s_obj_base
{
	/* data */
	char		*type;
	void		*obj;
	t_obj_base	*next;
	
}	t_obj_base;

t_obj_base *ft_obj_base_set(char *type, void *ptr);
t_obj_base *ft_obj_base_pushback(t_obj_base **obj_base_ptr, char *type, void *ptr);

#endif