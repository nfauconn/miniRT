/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:03:53 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/08 15:02:50 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_scene	scene;

 	if (ac != 2)
		return (error_display("format : ./miniRT <*.rt>"));
	setup_scene(&scene, av[1]);
	display_scene(&scene);
	return (0);
}

	/*provisoire :*/
/* 	(void)ac;
	(void)av;
	scene = setup_scene();*/
	/*************/
