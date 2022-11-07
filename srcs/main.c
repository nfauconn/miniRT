/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:03:53 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/07 19:47:47 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_scene	*scene;

 	if (ac != 2)
		return (error_display("format : ./miniRT <*.rt>"));
	scene = setup_scene(av[1]);
	/*provisoire :*/
/* 	(void)ac;
	(void)av;
	scene = setup_scene();*/
	/*************/

	display_scene(scene);
	return (0);
}
