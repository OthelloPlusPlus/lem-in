/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:47:38 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:07:35 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "common.h"

t_room*	create_room(char* name, u_int32_t x, u_int32_t y)
{
	t_room*	room;

	if (name == NULL)
		return (NULL);
	room = ft_calloc(1, sizeof(t_room));
	if (room == NULL)
		error_exit(ERR_CALLOC);
	room->name = ft_strdup(name);
	if (room->name == NULL)
	{
		free(room);
		return (NULL);
	}
	room->x = x;
	room->y = y;
	return (room);
}
