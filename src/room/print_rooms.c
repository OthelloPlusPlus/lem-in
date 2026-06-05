/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:21:43 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:07:44 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

static void	print_header(t_room* room);

void	print_rooms(t_rooms* rooms)
{
	t_room*	room;

	print_header(rooms->list);
	room = rooms->list;
	while (room != NULL)
	{
		if (room == rooms->start)
			ft_printf("##start\n");
		if (room == rooms->end)
			ft_printf("##end\n");
		print_room(room);
		room = room->next;
	}
}

static void	print_header(t_room* room)
{
	u_int32_t	count;

	count = 0;
	while (room != NULL)
	{
		++count;
		room = room->next;
	}
	ft_printf("\n# Rooms %u\n", count);
}

void	print_room(t_room* room)
{
	ft_printf("%s %u %u\n", room->name, room->x, room->y);
}
