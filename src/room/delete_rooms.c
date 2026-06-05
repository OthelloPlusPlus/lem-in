/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:38:18 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:07:56 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "common.h"

void	delete_room(t_room* room);

void	delete_rooms(t_rooms* rooms)
{
	t_room*	room;
	t_room*	temp;

	room = rooms->list;
	while (room != NULL)
	{
		temp = room;
		room = room->next;
		delete_room(temp);
	}
	rooms->list = NULL;
	rooms->start = NULL;
	rooms->end = NULL;
}

void	delete_room(t_room* room)
{
	free(room->name);
	free(room->links);
	free(room);
}
