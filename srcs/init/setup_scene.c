/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:19:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 12:04:43 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "setup.h"

static void	init(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	init_paramsetter(scene);
}

void	setup_scene(t_scene *scene, char *file)
{
	bool	ret;

	init(scene);
	ret = parse_file(file, scene);
	if (ret)
		exit_clear(FAIL, scene);
}
