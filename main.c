/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:28:42 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/13 12:00:04 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_app.h"
#include "mlx.h"
#include "ft_tool.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
	t_app	*app;
	
	/* code */
	(void)argc;
	(void)argv;
	app = ft_app_init();
	ft_app_execute(app);
	system("leaks a.out");
	(void)app;
	return 0;
}
