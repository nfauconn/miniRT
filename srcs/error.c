/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:20:41 by nfauconn          #+#    #+#             */
/*   Updated: 2022/10/25 17:42:25 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	error_display(char *s)
{
	ft_printerror("%s\n", s);
	return (1);
}

bool	error_display2(char *s1, char *s2)
{
	ft_printerror("%s: %s\n", s1, s2);
	return (1);
}
