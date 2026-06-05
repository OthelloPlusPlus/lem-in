/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ants_to_moves.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 19:57:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/04/24 21:15:54 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

static void	add_ants_to_move_list(t_ant* first, t_move* list);

void	add_ants_to_moves(t_farm* farm, t_moves* moves)
{
	while (moves != NULL)
	{
		add_ants_to_move_list(farm->ants.ants, moves->moves);
		moves = moves->next;
	}
}

static void	add_ants_to_move_list(t_ant* first, t_move* list)
{
	t_ant* ant;

	ant = first;
	while (list)
	{
		if (ant == NULL || ant->id > list->id)
			ant = first;
		while (ant != NULL && ant->id < list->id)
			ant = ant->next;
		list->ant = ant;
		list = list->next;
	}
}
