/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:03:53 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/04 17:46:20 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_scene	scene;

/* 	if (ac != 2)
		return (error_display("format : ./miniRT <*.rt>"));
	scene = scene_setup(av[1]);
	display(scene);	 */
	
	/*provisoire :*/
	(void)ac;
	(void)av;
	scene = scene_setup();
	/*************/

	display_scene(scene);
	return (0);
}
