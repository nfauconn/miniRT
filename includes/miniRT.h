/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:56:38 by nfauconn          #+#    #+#             */
/*   Updated: 2022/10/26 17:22:18 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libft/includes/libft.h"
# include "mlx.h"
# include <errno.h>

typedef enum e_elements
{
	ambientlight = 0,
	camera,
	lightsource,
	plan,
	sphere,
	cylindre
}	t_elements;

void	parse(char *scene);
bool	error_display(char *s);
bool	error_display2(char *s1, char *s2);

#endif
