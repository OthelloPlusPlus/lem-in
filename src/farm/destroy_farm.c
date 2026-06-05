/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_farm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:35:33 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:06:29 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "common.h"

static void	delete_storage(t_storage* storage);

void	destroy_farm(t_farm* farm)
{
	delete_rooms(&farm->rooms);
	delete_links(farm);
	delete_storage(farm->storage);
}

static void	delete_storage(t_storage* storage)
{
	t_storage*	temp;
	u_int32_t	i;

	while (storage != NULL)
	{
		ft_printf("#! ");
		i = 0;
		while (storage->array[i] != NULL)
		{
			ft_printf("%s ", storage->array[i]);
			free(storage->array[i]);
			++i;
		}
		ft_printf("\n");
		free(storage->array);
		temp = storage;
		storage = storage->next;
		free(temp);
	}
}
