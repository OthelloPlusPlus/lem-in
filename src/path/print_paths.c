/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:59:15 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/28 19:03:53 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_header(t_path* path);
static void	print_steps(t_step* step);
static void	print_path(t_path* path);

void	print_paths(t_path* paths)
{
	print_header(paths);
	while (paths != NULL)
	{
		print_path(paths);
		paths = paths->next;
	}
}

static void	print_header(t_path* path)
{
	u_int32_t	count;

	count = 0;
	while (path != NULL)
	{
		++count;
		path = path->next;
	}
	ft_printf("\n# Paths %u\n", count);
}

static void	print_path(t_path* path)
{
	// ft_printf("# Length %2i\n", path->length);
	ft_printf("# %2u ants", path->ants);
	print_steps(path->first);
}

static void	print_steps(t_step* step)
{
	while (step != NULL)
	{
		ft_printf(" > %s", step->room->name);
		step = step->next;
	}
	ft_printf("\n");
}
