/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_for_later.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:57:53 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:05:18 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

static void	print_array(char** array);

void	store_for_later(t_farm* farm, char** array)
{
	t_storage*	store;
	t_storage*	last;

	store = ft_calloc(1, sizeof(t_storage));
	if (store == NULL)
	{
		ft_dprintf(2, "#! "C_RED"Error:"C_RESET" Failed to store:");
		print_array(array);
		ft_dprintf(2, "\n");
		return ;
	}
	store->array = array;
	if (farm->storage == NULL)
		farm->storage = store;
	else
	{
		last = farm->storage;
		while (last->next != NULL)
			last = last->next;
		store->prev = last;
		last->next = store;
	}
}

static void	print_array(char** array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_dprintf(2, "%s ", array[i]);
		++i;
	}
}
