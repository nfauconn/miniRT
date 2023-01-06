/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:51:04 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/06 16:47:41 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static bool	parse_input(char *input, t_scene *scene)
{
	(void)input; (void)scene;
	return (0);
}

bool	get_input(t_scene *scene)
{
	bool	ret;
	char	*input;

	printf("\nenter the move you want to do\n\n");
	printf("format: <obj> <move> <new coord>\n");
	printf("possible moves : translate / rotate\n");
	printf("notation : t / r\n");
	input = get_next_line(0);
	ret = parse_input(input, scene);
	free(input);
	return (ret);
}