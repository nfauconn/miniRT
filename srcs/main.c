/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:03:53 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 13:06:45 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"
#include "exit.h"
#include "setup.h"
#include "display.h"

int	main(int ac, char **av)
{
	t_scene	scene;

 	if (ac != 2)
		return (error_display("format : ./miniRT <*.rt>"));
	setup_scene(&scene, av[1]);
	launch_display(&scene);
	return (0);
}
