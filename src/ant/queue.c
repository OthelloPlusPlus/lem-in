/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:38:02 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 19:03:17 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "lem_in.h"

void	add_ant_to_queue(t_queue** queue, t_ant* ant)
{
	t_queue*	attempt;
	t_queue*	last;

	attempt = ft_calloc(1, sizeof(t_queue));
	if (attempt == NULL)
		return ;
	attempt->ant = ant;
	if (queue == NULL || *queue == NULL)
	{
		*queue = attempt;
		return ;
	}
	last = *queue;
	while (last->next != NULL)
		last = last->next;
	last->next = attempt;
}

void	clear_queue(t_queue* queue)
{
	t_queue*	temp;

	while (queue != NULL)
	{
		ft_dprintf(2, C_RED"X%i-%s"C_RESET" ", queue->ant->id, queue->ant->route->room->name);
		temp = queue;
		queue = queue->next;
		free(temp);
	}
}
