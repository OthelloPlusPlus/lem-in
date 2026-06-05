/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_room_depths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:36:29 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/26 18:11:09 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "lem_in.h"

// static t_room*	get_dest_from_link(t_link* link, t_room* orig);

void	bfs_room_depths(t_farm* farm)
{
	t_bfs_queue	queue;
	t_bfs*		bfs;
	t_room*		room;
	int			i;

	t_room*	temp = farm->rooms.list;
	while (temp)
	{
		temp->depth = 0;
		temp = temp->next;
	}

	ft_memset(&queue, 0, sizeof(t_bfs_queue));
	add_room_to_queue(&queue, farm->rooms.start);
	farm->rooms.start->depth = 1;
	while (queue.first != NULL)
	{
		bfs = pop_queue(&queue);
// ft_print_debug("%s[%i]", bfs->room->name, bfs->room->depth);
		i = 0;
		while (bfs->room->links[i] != NULL)
		{
			// room = get_dest_from_link(bfs->room->links[i], bfs->room);
			room = bfs->room->links[i];
			if (room->depth == 0)
			{
				room->depth = bfs->room->depth + 1;
				add_room_to_queue(&queue, room);
			}
			++i;
		}
		free(bfs);
	}
}

// static t_room*	get_dest_from_link(t_link* link, t_room* orig)
// {
// 	if (link->room1 == orig)
// 		return (link->room2);
// 	if (link->room2 == orig)
// 		return (link->room1);
// 	return (NULL);
// }
