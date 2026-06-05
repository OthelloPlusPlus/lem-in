/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:04:36 by ohengelm          #+#    #+#             */
/*   Updated: 2026/06/05 19:45:46 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "lem_in.h"

static bool	bfs_new_path(t_farm* farm);
static void	set_start(t_bfs_queue* queue, t_room* start);
static bool	add_valid_dest_to_queue(t_bfs_queue* queue, t_room* orig, t_room* dest);

static void	adjust_in_and_out(t_room* route);
static void	unset_markers(t_room* room);
static void	distribute_ants(uint32_t ant_count, t_paths* paths);
static void	determine_turns(t_paths* paths);

// void	print_room_overview(t_room* room)
// {
// 	ft_dprintf(2, "#! %12s%12s%12s%12s%12s\n", "name", "in", "out", "parent", "depth");
// 	while (room != NULL)
// 	{
// 		// if (room->in)
// 		// {
// 			ft_dprintf(2, "#! %12s", room->name);
// 			if (room->in)
// 				ft_dprintf(2, "%12s", room->in->name);
// 			else
// 				ft_dprintf(2, "%12p", room->in);
// 			if (room->out)
// 				ft_dprintf(2, "%12s", room->out->name);
// 			else
// 				ft_dprintf(2, "%12p", room->out);
// 			if (room->parent)
// 				ft_dprintf(2, "%12s", room->parent->name);
// 			else
// 				ft_dprintf(2, "%12p", room->parent);
// 			ft_dprintf(2, "%12i\n", room->depth);
// 		// }
// 		room = room->next;
// 	}
// 	ft_dprintf(2, "\n");
// }

// void	print_rooms_with_adjusted_coords(t_farm* farm)
// {
// 	t_bfs_queue	queue;
// 	t_bfs*		bfs;
// 	t_room*		dest;

// 	int	current_depth;
// 	int	count;

// 	ft_memset(&queue, 0, sizeof(t_bfs_queue));
// 	add_room_to_queue(&queue, farm->rooms.start);
// 	farm->rooms.start->depth = 1;
// 	current_depth = 0;
// 	while (queue.first != NULL)
// 	{
// 		bfs = pop_queue(&queue);
// 		for (int i = 0; bfs->room->links[i] != NULL; ++i)
// 		{
// 			// dest = get_dest_from_link(bfs->room->links[i], bfs->room);
// 			dest = bfs->room->links[i];
// 			if (dest->depth == 0)
// 			{
// 				dest->depth = bfs->room->depth + 1;
// 				add_room_to_queue(&queue, dest);

// 				if (dest->depth > current_depth)
// 				{
// 					current_depth = dest->depth;
// 					count = 0;
// 				}
// 				++count;
// 				if (dest->y == 0)
// 					dest->y = count;
// 				// ft_printf("%s %i %i\n", dest->name, dest->depth, count);
// 			}
// 		}
// 	}
// 		free(bfs);
// 	exit(0);
// }

t_paths*	find_paths(t_farm* farm)
{
	t_paths*	best_path_set;
	t_paths*	candidate;

	best_path_set = NULL;
	unset_markers(farm->rooms.list);
	while (bfs_new_path(farm))
	{
		adjust_in_and_out(farm->rooms.end);
		unset_markers(farm->rooms.list);
		candidate = create_paths(&farm->rooms);
		paths_sort(candidate);
		distribute_ants(farm->ants.count, candidate);
		determine_turns(candidate);
		if (best_path_set == NULL)
			best_path_set = candidate;
		else if (candidate->turns < best_path_set->turns)
		{
			delete_paths(best_path_set);
			best_path_set = candidate;
		}
		else
			delete_paths(candidate);
	}
	if (best_path_set == NULL)
		error_exit(ERR_NO_PATHS);
	return (best_path_set);
}

////////////////////////////////////////////////////////////////////////////////

static bool	bfs_new_path(t_farm* farm)
{
	t_bfs_queue	queue;
	t_bfs*		node;
	t_room*		dest;
	int			i;

	set_start(&queue, farm->rooms.start);
	while (queue.first != NULL)
	{
		node = pop_queue(&queue);
		if (node->room == farm->rooms.end)
		{
			free(node);
			clear_bfs_queue(&queue);
			return (true);
		}
		i = 0;
		while (node->room->links[i] != NULL)
		{
			// dest = get_dest_from_link(node->room->links[i], node->room);
			dest = node->room->links[i];
			if (add_valid_dest_to_queue(&queue, node->room, dest) && (dest == farm->rooms.end || node->room == farm->rooms.end))
			{
				free(node);
				clear_bfs_queue(&queue);
				return (true);
			}
			++i;
		}
		free(node);
	}
	return (false);
}

static void	set_start(t_bfs_queue* queue, t_room* start)
{
	t_room*	dest;
	int		i;

	ft_memset(queue, 0, sizeof(t_bfs_queue));
	start->visited = true;
	i = 0;
	while (start->links[i])
	{
		dest = start->links[i];
		if (dest->in != start)
		{
			dest->visited = true;
			dest->parent = start;
			add_room_to_queue(queue, dest);
		}
		++i;
	}
}

static bool	add_valid_dest_to_queue(t_bfs_queue* queue, t_room* orig, t_room* dest)
{
	if (dest->visited == true)
		return (false);

	if (orig->in != NULL && \
		orig->in != dest && \
		orig->parent != orig->out)
		return (false);
	dest->visited = true;
	dest->parent = orig;
	add_room_to_queue(queue, dest);
	return (true);
}

////////////////////////////////////////////////////////////////////////////////

static void	adjust_in_and_out(t_room* route)
{
	t_room*	prev;
	t_room*	in;
	t_room*	out;

	prev = NULL;
	while (route != NULL)
	{
		// Default setting
		in = route->parent;
		out = prev;
		// Counter Current setting
		if (route->in == prev && route->out == route->parent)
		{
			in = NULL;
			out = NULL;
		}
		// Counter Current in
		else if (route->out == route->parent)
			in = route->in;
		// Counter Current out
		else if (route->in == prev)
			out = route->out;
		route->in = in;
		route->out = out;
		prev = route;
		route = route->parent;
	}
}

static void	unset_markers(t_room* room)
{
	while (room != NULL)
	{
		room->visited = false;
		room->parent = NULL;
		room = room->next;
	}
}

////////////////////////////////////////////////////////////////////////////////

static void	distribute_ants(uint32_t ant_count, t_paths* paths)
{
	t_path*	path;
	int		sum;

	sum = 0;
	while (ant_count > 0)
	{
		path = paths->first;
		while (path != NULL && ant_count > 0)
		{
			if (path->ants + path->length < sum)
			{
				++path->ants;
				--ant_count;
			}
			path = path->next;
		}
		++sum;
	}
}

static void	determine_turns(t_paths* paths)
{
	t_path*	path;

	path = paths->first;
	while (path != NULL)
	{
		if (paths->turns < path->length + path->ants)
			paths->turns = path->length + path->ants;
		path = path->next;
	}
}
