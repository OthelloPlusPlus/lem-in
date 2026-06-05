/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:55:46 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/19 14:57:33 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdlib.h>	// malloc, free, exit

void	add_room_to_queue(t_bfs_queue* queue, t_room* room)
{
	t_bfs*	new_node;

	if (queue == NULL)
		return;
	new_node = ft_calloc(1, sizeof(t_bfs));
	if (new_node == NULL)
		error_exit(ERR_CALLOC);
	new_node->room = room;
	if (queue->first == NULL)
		queue->first = new_node;
	if (queue->last != NULL)
		queue->last->next = new_node;
	queue->last = new_node;
}

t_bfs*	pop_queue(t_bfs_queue* queue)
{
	t_bfs*	node;

	node = queue->first;
	if (queue->first != NULL)
		queue->first = queue->first->next;
	if (queue->first == NULL)
		queue->last = NULL;
	return (node);
}

void	clear_bfs_queue(t_bfs_queue* queue)
{
	t_bfs*	node;

	while (queue->first != NULL)
	{
		node = pop_queue(queue);
		free(node);
	}
}
