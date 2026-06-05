/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:21:47 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 16:21:44 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "lem_in.h"

static t_path*	trace_flow_to_create_path(t_rooms* rooms, t_room* room);
// static void		add_path_to_paths(t_paths* paths, t_path* path);
static t_step*	create_step(t_room* room);

t_paths*	create_paths(t_rooms* rooms)
{
	t_paths*	new_set;
	t_path*		new_path;
	int			i;

	new_set = ft_calloc(1, sizeof(t_paths));
	if (new_set == NULL)
		error_exit(ERR_CALLOC);
	i = 0;
	while (rooms->start->links[i] != NULL)
	{
		// ft_dprintf(2, "#?");
		new_path = trace_flow_to_create_path(rooms, rooms->start->links[i]);
		// ft_dprintf(2, "\n");
		// step = trace_flow_to_create_path(step, rooms->start->links[i]);
		if (new_path->first->room == rooms->start && new_path->last->room == rooms->end)
			paths_push_back(new_set, new_path);
		else
			delete_path(new_path);
		++i;
	}
	if (new_set->first == NULL)
	{
		free(new_set);
		return (NULL);
	}
	return (new_set);
}

static t_path*	trace_flow_to_create_path(t_rooms* rooms, t_room* room)
{
	t_path*	path;

	path = ft_calloc(1, sizeof(t_path));
	if (path == NULL)
		error_exit(ERR_CALLOC);
	path->first = create_step(rooms->start);
	path->last = path->first;
	// ft_dprintf(2, " %4s", path->first->room->name);
	while (room != NULL)
	{
		path->last->next = create_step(room);
		if (path->last->next == NULL)
			error_exit(ERR_CALLOC);
		++path->length;
		path->last = path->last->next;
		// ft_dprintf(2, " %4s", path->last->room->name);
		room = room->out;
	}
	return (path);
}

// static void	add_path_to_paths(t_paths* paths, t_path* path)
// {
// 	if (paths == NULL || path == NULL)
// 		return ;
// 	// Add path to references
// 	if (paths->first == NULL)
// 		paths->first = path;
// 	if (paths->last != NULL)
// 		paths->last->next = path;
// 	paths->last = path;
// 	// Adjust meta data
// 	++paths->count;
// 	if (path->length > paths->longest)
// 		paths->longest = path->length;
// 	return ;
// }

static t_step*	create_step(t_room* room)
{
	t_step*	step;

	if (room == NULL)
		return (NULL);
	step = ft_calloc(1, sizeof(t_step));
	if (step == NULL)
		error_exit(ERR_CALLOC);
	step->room = room;
	return (step);
}
