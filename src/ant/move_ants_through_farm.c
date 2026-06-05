/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants_through_farm.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:53:20 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 20:44:46 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "lem_in.h"

static void	move_current_ants(t_ants* ants);
static bool	move_ant_to_next_step(t_ants* ants, t_ant* ant);
static void	assign_new_ants(t_ants* ants, t_path* path);
static void	retry_ants_in_queue(t_queue** queue, t_ants* ants);

void	move_ants_through_farm(t_farm* farm, t_path* path)
{
	int	lines;

	ft_printf("\n# Moves \n");
	lines = 0;
	// assign_new_ants(&farm->ants, path);
	while (farm->ants.ants != NULL)
	{
		move_current_ants(&farm->ants);
		assign_new_ants(&farm->ants, path);
		ft_printf("\n");
		++lines;
	}
	ft_printf("# Number of lines: %i\n", lines);
}

static void	assign_new_ants(t_ants* ants, t_path* path)
{
	t_ant* ant;

	ant = ants->ants;
	while (ant != NULL && ant->route != NULL)
		ant = ant->next;
	while (ant != NULL && path != NULL)
	{
		if (path->ants > 0 && path->first->next->room->ant == NULL)
		{
			--path->ants;
			ant->room = path->first->room;
			ant->route = path->first->next;
			move_ant_to_next_step(ants, ant);
			ant = ant->next;
		}
		path = path->next;
	}
}

static void	move_current_ants(t_ants* ants)
{
	t_ant*		ant;
	t_queue*	queue;
	t_ant*		next;

	ant = ants->ants;
	queue = NULL;
	while (ant != NULL && ant->route != NULL)
	{
		next = ant->next;
		if (move_ant_to_next_step(ants, ant))
		{
			if (queue != NULL)
				retry_ants_in_queue(&queue, ants);
		}
		else
			add_ant_to_queue(&queue, ant);
		ant = next;
	}
	clear_queue(queue);
}

static bool	move_ant_to_next_step(t_ants* ants, t_ant* ant)
{
	if (ant->route->room->ant != NULL)
		return (false);
	ant->room->ant = NULL;
	ant->room = ant->route->room;
	ant->room->ant = ant;
	ant->route = ant->route->next;
	ft_printf("L%u-%s ", ant->id, ant->room->name);
	if (ant->route == NULL)
		delete_ant(ants, ant);
	return (true);
}

static void	retry_ants_in_queue(t_queue** queue, t_ants* ants)
{
	t_queue*	crnt;
	t_queue*	prev;

	crnt = *queue;
	prev = NULL;
	while (crnt != NULL)
	{
		if (move_ant_to_next_step(ants, crnt->ant))
		{
			if (crnt == *queue)
				*queue = crnt->next;
			else
				prev->next = crnt->next;
			free(crnt);
			crnt = *queue;
			prev = NULL;
		}
		else
		{
			prev = crnt;
			crnt = crnt->next;
		}
	}
}
