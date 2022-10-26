/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:03:53 by nfauconn          #+#    #+#             */
/*   Updated: 2022/10/26 16:44:16 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


int	main(int ac, char **av)
{
	if (ac != 2)
		return (error_display("please enter a scene file"));
	parse(av[1]);
	return (0);
}
