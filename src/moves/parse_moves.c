/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:55:21 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 20:18:51 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_visual.h"

static t_move*	parse_move(t_farm* farm, char* string);
static t_move*	parse_move_list(t_farm* farm, char** array);

bool	parse_moves(t_ss* ss, char** array)
{
	t_move*		move;
	t_moves*	moves;
	t_moves*	last;

	move = parse_move_list(&ss->farm, array);
	if (move == NULL)
		return (false);
	moves = ft_calloc(1, sizeof(t_moves));
	if (moves == NULL)
	{
		delete_move_list(move);
		error_exit(ERR_CALLOC);
	}
	moves->moves = move;
	if (ss->moves == NULL)
		ss->moves = moves;
	else
	{
		last = ss->moves;
		while (last->next != NULL)
			last = last->next;
		last->next = moves;
	}
	return (true);
}

static t_move*	parse_move_list(t_farm* farm, char** array)
{
	t_move	start;
	t_move*	last;
	int		i;

	last = &start;
	i = 0;
	while (array[i] != NULL)
	{
		last->next = parse_move(farm, array[i]);
		if (last->next == NULL)
		{
			delete_move_list(start.next);
			return (NULL);
		}
		last = last->next;
		++i;
	}
	return (start.next);
}

static t_move*	parse_move(t_farm* farm, char* string)
{
	char**	array;
	t_move*	move;

	if (string == NULL || string[0] != MOVE_FLAG)
		return (NULL);
	array = ft_split(&string[1], '-');
	if (array == NULL)
		return (NULL);
	if (ft_array_len((void**)array) != 2)
	{
		ft_free_array(&array);
		return (NULL);
	}
	move = create_move(&farm->ants, ft_atoi(array[0]), farm->rooms.list, array[1]);
	ft_free_array(&array);
	if (move == NULL)
		return (NULL);
	if (move->id < 0 || move->id > (int)farm->ants.count || move->room == NULL)
		ft_free(&move);
	return (move);
}
