/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_from_storage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:40:10 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:05:47 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free, exit

#include "common.h"

void	remove_from_storage(t_storage** first, t_storage* storage)
{
	if (storage == NULL)
		return ;
	if (storage->prev)
		storage->prev->next = storage->next;
	if (storage->next)
		storage->next->prev = storage->prev;
	if (first && *first == storage)
		*first = storage->next;
	ft_free_array(&storage->array);
	free(storage);
}
