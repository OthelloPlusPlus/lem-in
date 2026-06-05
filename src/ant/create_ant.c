/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:30:56 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 20:44:33 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

t_ant*	create_ant(u_int32_t id, t_room* pos)
{
	t_ant*	ant;

	ant = ft_calloc(1, sizeof(t_ant));
	if (ant == NULL)
		error_exit(ERR_CALLOC);
	ant->id = id;
	if (pos != NULL)
	{
		ant->room = pos;
		ant->x = pos->x;
		ant->y = pos->y;
	}
	return (ant);
}
