/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link_to_farm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:54:49 by ohengelm          #+#    #+#             */
/*   Updated: 2026/05/15 18:09:57 by ohengelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	// NULL

#include "common.h"

void	add_link_to_farm(t_farm* farm, t_link* link)
{
	t_link*	ptr;

	if (farm->links == NULL)
		farm->links = link;
	else
	{
		ptr = farm->links;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = link;
	}
}
