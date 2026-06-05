/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:06:19 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 16:21:21 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "lem_in.h"

void	paths_push_back(t_paths* paths, t_path* last)
{
	if (paths == NULL || last == NULL)
		return ;
	// Add path to references
	if (paths->first == NULL)
		paths->first = last;
	if (paths->last)
		paths->last->next = last;
	paths->last = last;
	// Adjust meta data
	++paths->count;
	if (last->length > paths->longest)
		paths->longest = last->length;
}

////////////////////////////////////////////////////////////////////////////////

static void	swap_paths(t_path* p1, t_path* p2);

void	paths_sort(t_paths* paths)
{
	t_path*	node;
	t_path*	comp;

	node = paths->first;
	if (node == NULL)
		return ;

	while (node->next != NULL)
	{
		comp = node->next;
		while (comp != NULL)
		{
			if (node->length > comp->length ||\
				(node->length == comp->length && node->ants < comp->ants))
				swap_paths(node, comp);
			comp = comp->next;
		}
		node = node->next;
	}
}

static void	swap_paths(t_path* p1, t_path* p2)
{
	t_path	temp;

	// swap ants
	temp.ants = p1->ants;
	p1->ants = p2->ants;
	p2->ants = temp.ants;
	// swap length
	temp.length = p1->length;
	p1->length = p2->length;
	p2->length = temp.length;
	// swap steps
	temp.first = p1->first;
	temp.last = p1->last;
	p1->first = p2->first;
	p1->last = p2->last;
	p2->first = temp.first;
	p2->last = temp.last;
}

////////////////////////////////////////////////////////////////////////////////

// void	paths_clear(t_paths* paths, bool unused_only)
// {
// 	t_path*	node;
// 	t_path*	prev;
// 	t_path*	temp;

// 	node = paths->first;
// 	prev = NULL;
// 	while (node != NULL)
// 	{
// 		if (!unused_only || node->ants == 0)
// 		{
// 			temp = node;
// 			if (prev == NULL)
// 				paths->first = node->next;
// 			else
// 				prev->next = node->next;
// 			node = node->next;
// 			free(temp);
// 		}
// 		else
// 		{
// 			prev = node;
// 			node = node->next;
// 		}
// 	}
// }

void	delete_steps(t_step* steps)
{
	t_step*	del;

	while(steps != NULL)
	{
		del = steps;
		steps = steps->next;
		free(del);
	}
}

void	delete_path(t_path* path)
{
	delete_steps(path->first);
	free(path);
}

void	delete_paths(t_paths* paths)
{
	t_path*	del;

	while (paths->first != NULL)
	{
		del = paths->first;
		paths->first = paths->first->next;
		delete_path(del);
	}
	free(paths);
}
