/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room_to_farm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:06:04 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:08:22 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

void	add_room_to_farm(t_farm* farm, t_room* room, t_room** dst)
{
	t_room* ptr;

	if (room == NULL)
		return ;
	if (farm->rooms.list == NULL)
		farm->rooms.list = room;
	else
	{
		ptr = farm->rooms.list;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = room;
	}
	if (dst != NULL)
	{
		if (*dst != NULL)
			error_exit(ERR_ROOM_SPECIAL_DOUBLE(room->name));
		*dst = room;
	}
}
